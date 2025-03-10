#include<stack>
#include "WindowUtils.h"
#include "D3D.h"
#include"gameManager.h"

void OnResize(int screenWidth, int screenHeight, MyD3D& d3d)
{
	d3d.OnResize_Default(screenWidth, screenHeight);
}
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	//int nSc;
	switch (message)
	{
	case WM_CHAR:
		switch (wParam)
		{
		case 27:
		case 'q':
		case 'Q':
			PostQuitMessage(0);
			return 0;
		default:
			gameManager::Instance().updateInput(wParam);
			break;
		}
	}

	return WinUtil::Get().DefaultMssgHandler(hWnd, message, wParam, lParam);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE prevInstance,
	PSTR cmdLine, int showCmd)
{
	int w(1024), h(768);
	if (!WinUtil::Get().InitMainWindow(w, h, hInstance, "What's the time?", WndProc, true))
		assert(false);
	MyD3D d3d;
	if (!d3d.InitDirect3D(OnResize))
		assert(false);
	WinUtil::Get().SetD3D(d3d);
	d3d.GetCache().SetAssetPath("../bin/data/");
	gameManager::Instance().Init(d3d);
	d3d.ReleaseD3D(true);
	return 0;
}