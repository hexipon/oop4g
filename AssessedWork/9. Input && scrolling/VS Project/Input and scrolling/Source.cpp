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
	switch (msg)
	{
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
		Game::mouseAndKeyInput.MessageEvent((HRAWINPUT)lParam);
		break;
	}

	return WinUtil::DefaultMssgHandler(hwnd, msg, wParam, lParam);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE prevInstance,
				   PSTR cmdLine, int showCmd)
{

	int w(512), h(256);
	if (!WinUtil::Get().InitMainWindow(w, h, hInstance, "Input and scrolling", MainWndProc, true))
		assert(false);

	d3d _d3d;
	if (!_d3d.InitDirect3D(OnResize))
		assert(false);
	WinUtil::Get().SetD3D(_d3d);
	_d3d.GetCache().SetAssetPath("assets/");
	Game game(_d3d);

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
	_d3d.ReleaseD3D(true);	
	return 0;
}

