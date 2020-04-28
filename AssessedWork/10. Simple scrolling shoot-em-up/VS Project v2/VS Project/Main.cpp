#include <windows.h>
#include <cassert>
#include <d3d11.h>

#include"d3d.h"
#include "WindowUtils.h"
#include"GameManager.h"
#include"gameConstants.h"

void OnResize(int screenWidth, int screenHeight, d3d& d3d)
{
	d3d.OnResize_Default(screenWidth, screenHeight);
}

LRESULT CALLBACK MainWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
		// Respond to keyboard event.
	case WM_CHAR:
		switch (wParam)
		{
		case 27:
		case 'q':
		case 'Q':
			PostQuitMessage(0);
			break;
		}
	case WM_INPUT:
		GameManager::mouseAndKeyInput.MessageEvent((HRAWINPUT)lParam);
		break;
	}

	return WindowUtils::DefaultMssgHandler(hwnd, msg, wParam, lParam);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE prevInstance, PSTR cmdLine, int showCmd)
{

	if (!WindowUtils::Get().InitMainWindow((int)gameConstants::WindowSize.x, (int)gameConstants::WindowSize.y, hInstance, "Simple shooter", MainWndProc, true))
		assert(false);

	d3d _d3d;
	if (!_d3d.InitDirect3D(OnResize))
		assert(false);
	WindowUtils::Get().SetD3D(_d3d);
	_d3d.GetCache().SetAssetPath("assets/");

	//initiate game manager and start game loop
	GameManager game(_d3d);
	GameManager::Get().Init();

	GameManager::Get().Release();
	_d3d.ReleaseD3D(true);
	return 0;
}

