#include "Gamepad.h"

using namespace std;

void Gamepad::Update()
{
	for (DWORD i = 0; i < XUSER_MAX_COUNT; i++)
	{
		State& s = mPads[i];
		s.port = -1;
		ZeroMemory(&s.state, sizeof(XINPUT_STATE));
		//if (XInputGetState(i, &s.state) == ERROR_SUCCESS)
		//{
			float normLX = fmaxf(-1, (float)s.state.Gamepad.sThumbLX / 32767);
			float normLY = fmaxf(-1, (float)s.state.Gamepad.sThumbLY / 32767);

			s.leftStickX = (abs(normLX) < s.deadzoneX ? 0 : (abs(normLX) - s.deadzoneX) * (normLX / abs(normLX)));
			s.leftStickY = (abs(normLY) < s.deadzoneY ? 0 : (abs(normLY) - s.deadzoneY) * (normLY / abs(normLY)));

			if (s.deadzoneX > 0)
				s.leftStickX *= 1 / (1 - s.deadzoneX);
			if (s.deadzoneY > 0)
				s.leftStickY *= 1 / (1 - s.deadzoneY);

			float normRX = fmaxf(-1, (float)s.state.Gamepad.sThumbRX / 32767);
			float normRY = fmaxf(-1, (float)s.state.Gamepad.sThumbRY / 32767);

			s.rightStickX = (abs(normRX) < s.deadzoneX ? 0 : (abs(normRX) - s.deadzoneX) * (normRX / abs(normRX)));
			s.rightStickY = (abs(normRY) < s.deadzoneY ? 0 : (abs(normRY) - s.deadzoneY) * (normRY / abs(normRY)));

			if (s.deadzoneX > 0)
				s.rightStickX *= 1 / (1 - s.deadzoneX);
			if (s.deadzoneY > 0)
				s.rightStickY *= 1 / (1 - s.deadzoneY);

			s.leftTrigger = (float)s.state.Gamepad.bLeftTrigger / 255;
			s.rightTrigger = (float)s.state.Gamepad.bRightTrigger / 255;

			s.port = i;
		//}
	}

}

void Gamepad::Initialise()
{
	for (int i = 0; i < XUSER_MAX_COUNT; ++i)
		mPads[i].port = -1;
}


bool Gamepad::IsPressed(int idx, unsigned short buttonId)
{
	assert(idx >= 0 && idx < XUSER_MAX_COUNT);
	assert(mPads[idx].port != -1);
	return (mPads[idx].state.Gamepad.wButtons & buttonId) != 0;
}

void Gamepad::GetAnalogueNames(int idx, std::wstring& mssg)
{
	assert(idx >= 0 && idx < XUSER_MAX_COUNT);
	State& s = mPads[idx];
	mssg = L"";
	if (s.port == -1)
		return;

	wstringstream str;
	str.precision(2);
	str << L"Left stick(x=" << s.leftStickX << L",y=" << s.leftStickY << L")";
	str << L" Right stick(x=" << s.rightStickX << L",y=" << s.rightStickY << L")";
	str << L" Trigger Left=" << s.leftTrigger << L", right=" << s.rightTrigger;
	mssg = str.str();
}

void Gamepad::GetDigitalNames(int idx, std::wstring& mssg)
{
	assert(idx >= 0 && idx < XUSER_MAX_COUNT);
	State& s = mPads[idx];
	mssg = L"";
	if (s.port == -1)
		return;

	wstringstream str;
	if (IsPressed(idx, XINPUT_GAMEPAD_DPAD_UP))
		str << L"DPAD_UP ";
	if (IsPressed(idx, XINPUT_GAMEPAD_DPAD_DOWN))
		str << L"DPAD DOWN ";
	if (IsPressed(idx, XINPUT_GAMEPAD_DPAD_LEFT))
		str << L"DPAD LEFT ";
	if (IsPressed(idx, XINPUT_GAMEPAD_DPAD_RIGHT))
		str << L"DPAD RIGHT ";
	if (IsPressed(idx, XINPUT_GAMEPAD_START))
		str << L"START ";
	if (IsPressed(idx, XINPUT_GAMEPAD_BACK))
		str << L"BACK ";
	if (IsPressed(idx, XINPUT_GAMEPAD_LEFT_THUMB))
		str << L"LEFT THUMB ";
	if (IsPressed(idx, XINPUT_GAMEPAD_RIGHT_THUMB))
		str << L"RIGHT THUMB ";
	if (IsPressed(idx, XINPUT_GAMEPAD_LEFT_SHOULDER))
		str << L"LEFT SHOULDER ";
	if (IsPressed(idx, XINPUT_GAMEPAD_RIGHT_SHOULDER))
		str << L"RIGHT SHOULDER ";
	if (IsPressed(idx, XINPUT_GAMEPAD_A))
		str << L"A ";
	if (IsPressed(idx, XINPUT_GAMEPAD_B))
		str << L"B ";
	if (IsPressed(idx, XINPUT_GAMEPAD_X))
		str << L"X ";
	if (IsPressed(idx, XINPUT_GAMEPAD_Y))
		str << L"Y ";
	mssg = str.str();
}