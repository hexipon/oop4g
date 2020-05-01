#pragma once
#include <Windows.h>
#include <Xinput.h>
#include "d3d.h"
#include "SimpleMath.h"
class Gamepad
{
public:
	struct State
	{
		int port = -1;
		float leftStickX = 0;
		float leftStickY = 0;
		float rightStickX = 0;
		float rightStickY = 0;
		float leftTrigger = 0;
		float rightTrigger = 0;
		float deadzoneX = 0.1f;
		float deadzoneY = 0.1f;
		XINPUT_STATE state;
	};
	void SetDeadZone(int idx, float x, float y) {
		assert(idx >= 0 && idx < XUSER_MAX_COUNT);
		mPads[idx].deadzoneX = x;
		mPads[idx].deadzoneY = y;
	}
	const State& GetState(int idx) const {
		assert(idx >= 0 && idx < XUSER_MAX_COUNT);
		return mPads[idx];
	}
	void Initialise();
	bool IsConnected(int idx) {
		assert(idx >= 0 && idx < XUSER_MAX_COUNT);
		return mPads[idx].port != -1;
	}
	void Update();
	bool IsPressed(int idx, unsigned short buttonId);
	void GetAnalogueNames(int idx, std::wstring& mssg);
	void GetDigitalNames(int idx, std::wstring& mssg);
private:
	State mPads[XUSER_MAX_COUNT];

};