#include <windows.h>
#include <string>
#include <cassert>
#include <d3d11.h>
#include <iomanip>
#include<stack>
#include<vector>
#include<string>
#include "WindowUtils.h"
#include "D3DUtil.h"
#include "D3D.h"
#include "SimpleMath.h"
#include "SpriteFont.h"
#include"State.h"
#include"Game.h"
#include"DiceGame.h"
#include"nameInput.h"
#include"End.h"

namespace
{
	Game *game = nullptr;
	MyD3D *d3d = nullptr;
};

void OnResize(int screenWidth, int screenHeight, MyD3D& d3d)
{
	d3d.OnResize_Default(screenWidth, screenHeight);
}
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{


	//auto game = reinterpret_cast<Game*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));
	int nSc;
	switch (message)
	{
	case WM_CHAR:
			game->states.top()->updateInput(wParam);
		switch (wParam)
		{
		case 8:
			game->states.top()->backspace();
			break;
		case 13:
			nSc = game->states.top()->getNextScene();
			game->nextScene(*d3d,nSc);
			break;
		case 27:
		case 'q':
		case 'Q':
			PostQuitMessage(0);
			return 0;
		}
	}

	return WinUtil::Get().DefaultMssgHandler(hWnd, message, wParam, lParam);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE prevInstance,
	PSTR cmdLine, int showCmd)
{
	int w(1024), h(768);
	if (!WinUtil::Get().InitMainWindow(w, h, hInstance, "Fezzy", WndProc, true))
		assert(false);

	d3d = new MyD3D;
	if (!d3d->InitDirect3D(OnResize))
		assert(false);
	WinUtil::Get().SetD3D(*d3d);
	game = new Game();
	game->init(*d3d);
	d3d->ReleaseD3D(true);
	return 0;
}