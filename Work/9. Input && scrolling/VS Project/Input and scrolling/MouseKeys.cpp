#include "MouseKeys.h"

using namespace std;
using namespace DirectX;
using namespace DirectX::SimpleMath;

bool MouseKeys::IsPressed(unsigned short vkeyCode) const
{
	assert(vkeyCode < KEYBUFF_SIZE);
	bool pressed = mKeyBuffer[vkeyCode] != 0;

	return pressed;
}

void MouseKeys::Reset()
{
	ZeroMemory(mInBuffer, sizeof(mInBuffer));
	ZeroMemory(mKeyBuffer, sizeof(mKeyBuffer));
	mButtons[0] = mButtons[1] = mButtons[2] = false;
	mMouseScreen = mMouseMove = DirectX::SimpleMath::Vector2(0, 0);
}


void MouseKeys::ProcessKeys(RAWINPUT* raw)
{
	//standard key code
	unsigned short flags = raw->data.keyboard.Flags;
	unsigned short vkey = raw->data.keyboard.VKey;
	unsigned short scanCode = raw->data.keyboard.MakeCode;

	//ignore keys we don't want
	if (vkey >= 255)
		return;

	if (vkey == VK_SHIFT)
	{
		// correct left-hand / right-hand SHIFT (VK_LSHIFT / VK_RSHIFT)
		vkey = MapVirtualKey(scanCode, MAPVK_VSC_TO_VK_EX);
	}
	else if (vkey == VK_NUMLOCK)
	{
		// correct PAUSE/BREAK and NUM LOCK silliness, and set the extended bit
		scanCode = (MapVirtualKey(vkey, MAPVK_VK_TO_VSC) | 0x100);
	}

	// e0 and e1 are escape sequences used for certain special keys, such as PRINT and PAUSE/BREAK.
	const bool isE0 = ((flags & RI_KEY_E0) != 0);
	const bool isE1 = ((flags & RI_KEY_E1) != 0);

	if (isE1)
	{
		if (vkey == VK_PAUSE)
			scanCode = 0x45;
		else
			scanCode = MapVirtualKey(vkey, MAPVK_VK_TO_VSC);
	}


	switch (vkey)
	{
		// right-hand CONTROL and ALT have their e0 bit set
	case VK_CONTROL:
		if (isE0)
			vkey = VK_RCONTROL; //right control
		else
			vkey = VK_LCONTROL;  //left control
		break;

	case VK_MENU:
		if (isE0)
			vkey = VK_RALT;  //right alt
		else
			vkey = VK_LALT;	//left alt
		break;

		// NUMPAD ENTER has its e0 bit set
	case VK_RETURN:
		if (isE0)
			vkey = VK_NUMPAD_ENTER; //numpad enter
		break;
	}
	//ignore anything larger than this, escape codes, fake keys or weird keys
	if (vkey >= 255)
		return;

	if (flags & RI_KEY_BREAK) //key up
		mKeyBuffer[vkey] = 0;
	else
		mKeyBuffer[vkey] = scanCode;
}

void MouseKeys::ProcessMouse(RAWINPUT* raw)
{
	unsigned short flags = raw->data.mouse.usButtonFlags;

	if (flags & RI_MOUSE_LEFT_BUTTON_DOWN)
		mButtons[LBUTTON] = true;
	if (flags & RI_MOUSE_LEFT_BUTTON_UP)
		mButtons[LBUTTON] = false;
	if (flags & RI_MOUSE_MIDDLE_BUTTON_DOWN)
		mButtons[MBUTTON] = true;
	if (flags & RI_MOUSE_MIDDLE_BUTTON_UP)
		mButtons[MBUTTON] = false;
	if (flags & RI_MOUSE_RIGHT_BUTTON_DOWN)
		mButtons[RBUTTON] = true;
	if (flags & RI_MOUSE_RIGHT_BUTTON_UP)
		mButtons[RBUTTON] = false;

	Vector2 last(mMouseScreen);
	GetMousePosAbsolute(mMouseScreen);
	mMouseMove = mMouseScreen - last;
}

void MouseKeys::GetMousePosAbsolute(Vector2& pos)
{
	POINT mpos;
	if (GetCursorPos(&mpos))
	{
		if (ScreenToClient(mHwnd, &mpos))
		{
			pos = Vector2((float)mpos.x, (float)mpos.y);
		}
	}

}

void MouseKeys::MessageEvent(HRAWINPUT rawInput)
{
	UINT dwSize;
	UINT res = GetRawInputData(rawInput, RID_INPUT, NULL, &dwSize, sizeof(RAWINPUTHEADER));
	if (res != 0)
		return;

	if (dwSize >= RAWBUFF_SIZE)
	{
		DBOUT("Buffer too small. Is " << RAWBUFF_SIZE << " wants " << dwSize);
		assert(false);
	}

	if (GetRawInputData(rawInput, RID_INPUT, mInBuffer, &dwSize, sizeof(RAWINPUTHEADER)) != dwSize)
	{
		DBOUT("GetRawInputData failed");
		assert(false);
	}

	RAWINPUT* raw = (RAWINPUT*)mInBuffer;

	if (raw->header.dwType == RIM_TYPEKEYBOARD)
	{
		ProcessKeys(raw);
	}
	else if (raw->header.dwType == RIM_TYPEMOUSE)
	{
		ProcessMouse(raw);
	}
}

void MouseKeys::GetPressedKeyNames(wstring& mssg)
{
	mssg = L"";
	for (int i = 0; i < KEYBUFF_SIZE; ++i)
	{
		if (mKeyBuffer[i] == 0)
			continue;
		//assume codes refer to arrow keys
		switch (i)
		{
		case VK_RIGHT:
			mssg += L"RIGHT ARROW ";
			break;
		case VK_LEFT:
			mssg += L"LEFT ARROW ";
			break;
		case VK_UP:
			mssg += L"UP ARROW ";
			break;
		case VK_DOWN:
			mssg += L"DOWN ARROW ";
			break;
		default:
			wchar_t key[256];
			if (GetKeyNameTextW(mKeyBuffer[i] << 16, key, sizeof(key)))
			{
				mssg += key;
				mssg += L" ";
			}
		}

	}
}



void MouseKeys::GetMouseNames(wstring& mssg)
{
	mssg = L"";
	static float oldX = 0, oldY = 0;
	if (!Equals(mMouseMove.x, 0))
		oldX = mMouseMove.x;
	if (!Equals(mMouseMove.y, 0))
		oldY = mMouseMove.y;
	wstringstream str;
	str.precision(0);
	str << L"x=" << mMouseScreen.x << L" y=" << mMouseScreen.y;
	str << L" xinc=" << oldX << L" yinc=" << oldY;
	if (mButtons[LBUTTON])
		str << L" LButton";
	if (mButtons[MBUTTON])
		str << L" MButton";
	if (mButtons[RBUTTON])
		str << L" RButton";

	mssg = str.str();
}

void MouseKeys::Initialise(HWND hwnd, bool showMouse, bool confineMouse)
{
	mHwnd = hwnd;

	RAWINPUTDEVICE Rid[2];

	//these ids trigger mouse input
	Rid[0].usUsagePage = 0x01;
	Rid[0].usUsage = 0x02;
	Rid[0].dwFlags = RIDEV_INPUTSINK; // adds HID mouse and also ignores legacy mouse messages
	Rid[0].hwndTarget = hwnd;

	//these ids trigger keyboard input
	Rid[1].usUsagePage = 0x01;
	Rid[1].usUsage = 0x06;
	Rid[1].dwFlags = RIDEV_INPUTSINK; // adds HID keyboard and also ignores legacy keyboard messages
	Rid[1].hwndTarget = hwnd;

	if (RegisterRawInputDevices(Rid, 2, sizeof(Rid[0])) == FALSE) {
		MessageBox(0, "Cannot get keyboard and mouse input", 0, 0);
		assert(false);
	}

	ShowCursor(showMouse);
	mConfineMouse = confineMouse;
	GetClipCursor(&mOldClip);
	if (mConfineMouse)
	{
		GetWindowRect(hwnd, &mNewClip);
		ClipCursor(&mNewClip);
	}
	GetMousePosAbsolute(mMouseScreen);
}

void MouseKeys::OnLost()
{
	Reset();
	ClipCursor(&mOldClip);
}

void MouseKeys::OnReset()
{
	Reset();
	ClipCursor(&mNewClip);
}

void MouseKeys::PostProcess()
{
	mMouseMove.x = 0;
	mMouseMove.y = 0;
}