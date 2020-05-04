#include "Gamepad.h"

using namespace std;

void Gamepad::Update()
{
	for (DWORD i = 0; i < XUSER_MAX_COUNT; i++)
	{
		State& s = mPads[i];
		s.port = -1;
		ZeroMemory(&s.state, sizeof(XINPUT_STATE));
		XInputGetState(i, &s.state);
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