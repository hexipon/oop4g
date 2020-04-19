#pragma once
#include <Windows.h>
#include <Xinput.h>
#include "d3d.h"
#include "SimpleMath.h"
class Gamepad
{
public:
	//gamepad data, one per pad
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
	//as a mechanical device the pad may generate data even when
	//nobody is touching it, especially if it's old. The deadzone
	//specifies a small range of input that will be ignored.
	//idx=which pad
	//x+y=range to ignore
	void SetDeadZone(int idx, float x, float y) {
		assert(idx >= 0 && idx < XUSER_MAX_COUNT);
		mPads[idx].deadzoneX = x;
		mPads[idx].deadzoneY = y;
	}
	//look at the state of a pad
	//idx=pad 0,1,2 or 3
	const State& GetState(int idx) const {
		assert(idx >= 0 && idx < XUSER_MAX_COUNT);
		return mPads[idx];
	}
	//called once at startup
	void Initialise();
	//check that a specific pad is still plugged in
	bool IsConnected(int idx) {
		assert(idx >= 0 && idx < XUSER_MAX_COUNT);
		return mPads[idx].port != -1;
	}
	//called every update
	void Update();

	/*
	Is the user holding down a button or stick
	XINPUT_GAMEPAD_DPAD_UP
	XINPUT_GAMEPAD_DPAD_DOWN
	XINPUT_GAMEPAD_DPAD_LEFT
	XINPUT_GAMEPAD_DPAD_RIGHT
	XINPUT_GAMEPAD_START
	XINPUT_GAMEPAD_BACK
	XINPUT_GAMEPAD_LEFT_THUMB
	XINPUT_GAMEPAD_RIGHT_THUMB
	XINPUT_GAMEPAD_LEFT_SHOULDER
	XINPUT_GAMEPAD_RIGHT_SHOULDER
	XINPUT_GAMEPAD_A
	XINPUT_GAMEPAD_B
	XINPUT_GAMEPAD_X
	XINPUT_GAMEPAD_Y
	*/
	bool IsPressed(int idx, unsigned short buttonId);
	//get a list of pad activity - motion of sticks and triggers
	void GetAnalogueNames(int idx, std::wstring& mssg);
	//get a list of pad activity - button presses
	void GetDigitalNames(int idx, std::wstring& mssg);
private:
	//a copy of state for each of 4 pads
	State mPads[XUSER_MAX_COUNT];

};