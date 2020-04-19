#pragma once
#include "D3D.h"
#include "d3dutil.h"

class MouseKeys
{
public:
	MouseKeys()
	{
		Reset();

	}
	//zero and forget everything so we can start again
	void Reset();
	//start up the mouse/keys system, call once only
	//hwnd - main windows handle
	//showMouse - hide the mouse cursor
	//confineMouse - prevent the mouse leaving the window
	void Initialise(HWND hwnd, bool showMouse = true, bool confineMouse = false);
	//a text list of all keys being held down
	void GetPressedKeyNames(std::wstring& mssg);
	//is a specific key down?
	bool IsPressed(unsigned short vkeyCode) const;
	//a text list of all mouse buttons and cursor position info
	void GetMouseNames(std::wstring& mssg);
	//check if a button is currently down
	typedef enum { LBUTTON = 0, MBUTTON = 1, RBUTTON = 2 } ButtonT;
	bool GetMouseButton(ButtonT b) const {
		return mButtons[b];
	}
	//get relative or absolute mouse position
	//absolute=true, 2D windows coordinates of cursor
	//absolute=false, 2D windows coordinate change in position since last update (push)
	DirectX::SimpleMath::Vector2 GetMousePos(bool absolute) const {
		if (absolute)
			return mMouseScreen;
		return mMouseMove;
	}
	//call this after game has finished using the mouse, probably at end of render
	void PostProcess();
	//for consistency we can reset mouse input after task switch (window<->fullscreen), optional
	void OnLost();
	void OnReset();

	//add to your windows message pump
	//rawInput comes from lparam after a WM_INPUT message
	//case WM_INPUT:
	//	input.MessageEvent((HRAWINPUT)lParam);
	void MessageEvent(HRAWINPUT rawInput);

private:
	//copy of main window handle
	HWND mHwnd;
	enum { RAWBUFF_SIZE = 512, KEYBUFF_SIZE = 255, KMASK_IS_DOWN = 1, MAX_BUTTONS = 3 };
	//raw input buffer
	BYTE mInBuffer[RAWBUFF_SIZE];
	unsigned short mKeyBuffer[KEYBUFF_SIZE];  //virtual key codes, but only the standard ones (first 256)
	//support for three mouse buttons
	bool mButtons[MAX_BUTTONS];
	//track mouse position changes (2D)
	DirectX::SimpleMath::Vector2 mMouseScreen, mMouseMove;
	//if the mouse is confined, track the size of the window
	bool mConfineMouse;
	RECT mNewClip;           // new area for ClipCursor
	RECT mOldClip;        // previous area for ClipCursor

	void ProcessKeys(RAWINPUT* raw);
	void ProcessMouse(RAWINPUT* raw);
	void GetMousePosAbsolute(DirectX::SimpleMath::Vector2& pos);
};

