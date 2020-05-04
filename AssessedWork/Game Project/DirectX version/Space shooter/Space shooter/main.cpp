#include <windows.h>
#include <cassert>
#include <d3d11.h>

#include"d3d.h"
#include "WindowUtils.h"
#include"gameData.h"
#include"Manager.h"
#include"FontCache.h"

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
			PostQuitMessage(0);
			break;
		}
	case WM_INPUT:
		Manager::mouseAndKeyInput.MessageEvent((HRAWINPUT)lParam);
		break;
	}

	return WindowUtils::DefaultMssgHandler(hwnd, msg, wParam, lParam);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE prevInstance, PSTR cmdLine, int showCmd)
{
	gameData gData;
	FontCache fCache;
	if (!WindowUtils::Get().InitMainWindow((int)gameData::Get().DefaultWindowSize.x, (int)gameData::Get().DefaultWindowSize.y, hInstance, "Simple shooter", MainWndProc, true))
		assert(false);
	d3d _d3d;
	if (!_d3d.InitDirect3D(OnResize))
		assert(false);
	WindowUtils::Get().SetD3D(_d3d);
	_d3d.GetCache().SetAssetPath("../Assets/");
	FontCache::Get().SetAssetPath("../Assets/Fonts/");
	//initiate game manager and start game loop
	Manager gameManager(_d3d);
	Manager::Get().startGameLoop();
	return 0;
}