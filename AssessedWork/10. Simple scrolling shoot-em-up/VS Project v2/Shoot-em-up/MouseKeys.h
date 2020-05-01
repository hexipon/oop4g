#pragma once
#include "D3D.h"
#include "d3dutils.h"

class MouseKeys
{
public:
	MouseKeys()
	{
		Reset();

	}
	void Reset();
	void Initialise(HWND hwnd, bool showMouse = true, bool confineMouse = false);
	void GetPressedKeyNames(std::wstring& mssg);
	bool IsPressed(unsigned short vkeyCode) const;
	void GetMouseNames(std::wstring& mssg);
	typedef enum { LBUTTON = 0, MBUTTON = 1, RBUTTON = 2 } ButtonT;
	bool GetMouseButton(ButtonT b) const {
		return mButtons[b];
	}
	DirectX::SimpleMath::Vector2 GetMousePos(bool absolute) const {
		if (absolute)
			return mMouseScreen;
		return mMouseMove;
	}
	void PostProcess();
	void OnLost();
	void OnReset();
	void MessageEvent(HRAWINPUT rawInput);

private:
	HWND mHwnd;
	enum { RAWBUFF_SIZE = 512, KEYBUFF_SIZE = 255, KMASK_IS_DOWN = 1, MAX_BUTTONS = 3 };
	BYTE mInBuffer[RAWBUFF_SIZE];
	unsigned short mKeyBuffer[KEYBUFF_SIZE];
	bool mButtons[MAX_BUTTONS];
	DirectX::SimpleMath::Vector2 mMouseScreen, mMouseMove;
	bool mConfineMouse;
	RECT mNewClip;
	RECT mOldClip;

	void ProcessKeys(RAWINPUT* raw);
	void ProcessMouse(RAWINPUT* raw);
	void GetMousePosAbsolute(DirectX::SimpleMath::Vector2& pos);
};

