#include <windows.h>
#include <string>
#include <cassert>
#include <d3d11.h>
#include <vector>

#include "WinUtil.h"

#include "Game.h"

using namespace std;
using namespace DirectX;
using namespace DirectX::SimpleMath;






void OnResize(int screenWidth, int screenHeight, d3d& d3d)
{
	d3d.OnResize_Default(screenWidth, screenHeight);
}

LRESULT CALLBACK MainWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	//do something game specific here
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
		Game::sMKIn.MessageEvent((HRAWINPUT)lParam);
		break;
	}

	//default message handling (resize window, full screen, etc)
	return WinUtil::DefaultMssgHandler(hwnd, msg, wParam, lParam);
}

//main entry point for the game
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE prevInstance,
				   PSTR cmdLine, int showCmd)
{

	int w(512), h(256);
	if (!WinUtil::Get().InitMainWindow(w, h, hInstance, "Input and scrolling", MainWndProc, true))
		assert(false);

	d3d md3d;
	if (!md3d.InitDirect3D(OnResize))
		assert(false);
	WinUtil::Get().SetD3D(md3d);
	md3d.GetCache().SetAssetPath("assets/");
	Game game(md3d);

	bool canUpdateRender;
	float dTime = 0;
	while (WinUtil::Get().BeginLoop(canUpdateRender))
	{
		if (canUpdateRender && dTime>0)
		{
			game.Update(dTime);
			game.Render(dTime);
		}
		dTime = WinUtil::Get().EndLoop(canUpdateRender);
	}

	game.Release();
	md3d.ReleaseD3D(true);	
	return 0;
}

