#include<stack>
#include "WindowUtils.h"
#include "D3D.h"
#include"Game.h"

void OnResize(int screenWidth, int screenHeight, MyD3D& d3d)
{
	d3d.OnResize_Default(screenWidth, screenHeight);
}
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int nSc;
	switch (message)
	{
	case WM_CHAR:
			Game::Instance().states.top()->updateInput(wParam);
		switch (wParam)
		{
		case 8:
			Game::Instance().states.top()->backspace();
			break;
		case 13:
			nSc = Game::Instance().states.top()->getNextScene();
			Game::Instance().nextScene(MyD3D::Instance(),nSc);
			break;
		case 27:
		case 'q':
		case 'Q':
			Game::Instance().ReleaseGame();
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
	if (!WinUtil::Get().InitMainWindow(w, h, hInstance, "Sixes", WndProc, true))
		assert(false);

	if (!MyD3D::Instance().InitDirect3D(OnResize))
		assert(false);
	WinUtil::Get().SetD3D(MyD3D::Instance());
	Game::Instance().init(MyD3D::Instance());
	MyD3D::Instance().ReleaseD3D(true);
	return 0;
}