#include "WindowUtils.h"
#include "D3D.h"

HINSTANCE WinUtil::GetAppInst()
{
	return mWinData.hAppInst;
}

HWND WinUtil::GetMainWnd()
{
	return mWinData.hMainWnd;
}

void WinUtil::GetClientExtents(int& width, int& height) const
{
	width = mWinData.clientWidth;
	height = mWinData.clientHeight;
}

LRESULT WinUtil::RealDefaultMssgHandler(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
		// pause the game when the window is deactivated and unpause it 
		// when it becomes active.  
	case WM_ACTIVATE:
		if (LOWORD(wParam) == WA_INACTIVE)
		{
			mWinData.appPaused = true;
		}
		else
		{
			mWinData.appPaused = false;
		}
		return 0;

		//destroy window
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;

	case WM_MENUCHAR:
		// Don't beep when we alt-enter.
		return MAKELRESULT(0, MNC_CLOSE);

	}

	return DefWindowProc(hwnd, msg, wParam, lParam);
}



bool WinUtil::InitMainWindow(int width, int height, HINSTANCE hInstance, const std::string& appName, WNDPROC mssgHandler, bool centred)
{
	// Enable run-time memory check for debug builds.
#if defined(DEBUG) | defined(_DEBUG)
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

	assert(mssgHandler);
	mWinData.mainWndCaption = appName;
	mWinData.hAppInst = hInstance;
	mWinData.clientWidth = width;
	mWinData.clientHeight = height;

	WNDCLASS wc;
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = mssgHandler;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = mWinData.hAppInst;
	wc.hIcon = LoadIcon(0, IDI_APPLICATION);
	wc.hCursor = LoadCursor(0, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(NULL_BRUSH);
	wc.lpszMenuName = 0;
	wc.lpszClassName = "D3DWndClassName";

	if (!RegisterClass(&wc))
	{
		MessageBox(0, "RegisterClass Failed.", 0, 0);
		return false;
	}

	// Compute window rectangle dimensions based on requested client area dimensions.
	RECT R = { 0, 0, mWinData.clientWidth, mWinData.clientHeight };
	AdjustWindowRect(&R, (WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU), false);
	int w = R.right - R.left;
	int h = R.bottom - R.top;

	int offsetX = CW_USEDEFAULT, offsetY = CW_USEDEFAULT;
	if (centred) {
		offsetY = (GetSystemMetrics(SM_CYSCREEN) - h) / 2;
		offsetX = (GetSystemMetrics(SM_CXSCREEN) - w) / 2;
	}
	mWinData.hMainWnd = CreateWindow("D3DWndClassName", mWinData.mainWndCaption.c_str(),
		(WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU), offsetX, offsetY, w, h, 0, 0, mWinData.hAppInst, 0);
	if (!mWinData.hMainWnd)
	{
		MessageBox(0, "CreateWindow Failed.", 0, 0);
		return false;
	}

	ShowWindow(mWinData.hMainWnd, SW_SHOW);
	UpdateWindow(mWinData.hMainWnd);

	return true;
}




bool WinUtil::BeginLoop(bool& canUpdateRender)
{
	MSG msg = { 0 };
	canUpdateRender = false;

	// If there are Window messages then process them.
	if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
		if (msg.message == WM_QUIT)
			return false;
		return true;
	}

	if (!mWinData.appPaused)
	{
		canUpdateRender = true;
	}

	return true;
}


float WinUtil::EndLoop(bool didUpdateRender)
{
	if (!didUpdateRender)
		return 0;
	float deltaTime = 0;
	if (!mWinData.appPaused)
	{
		__int64 countsPerSec;
		QueryPerformanceFrequency((LARGE_INTEGER*)&countsPerSec);
		double secondsPerCount = 1.0 / (double)countsPerSec;
		static __int64 sTime1 = 0;
		__int64 time2;
		QueryPerformanceCounter((LARGE_INTEGER*)&time2);
		if (sTime1 != 0)
			deltaTime = (float)((time2 - sTime1)*secondsPerCount);
		sTime1 = time2;
		AddSecToClock(deltaTime);

	}
	else
	{
		Sleep(100);
	}
	return deltaTime;
}

int WinUtil::Run(void(*pUpdate)(float), void(*pRender)(float))
{
	MSG msg = { 0 };
	assert(pUpdate && pRender);

	__int64 countsPerSec;
	QueryPerformanceFrequency((LARGE_INTEGER*)&countsPerSec);
	double secondsPerCount = 1.0 / (double)countsPerSec;

	float deltaTime = 0;
	while (msg.message != WM_QUIT)
	{
		// If there are Window messages then process them.
		if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		// Otherwise, do animation/game stuff.
		else
		{
			if (!mWinData.appPaused)
			{

				if (!mWinData.appPaused)
					pUpdate(deltaTime);
				pRender(deltaTime);

				static __int64 sTime1 = 0;
				__int64 time2;
				QueryPerformanceCounter((LARGE_INTEGER*)&time2);
				if (sTime1 != 0)
					deltaTime = (float)((time2 - sTime1)*secondsPerCount);
				sTime1 = time2;
				AddSecToClock(deltaTime);
			}
			else
			{
				Sleep(100);
			}
		}
	}
	return (int)msg.wParam;
}

void WinUtil::ChooseRes(int& w, int& h, int defaults[], int numPairs)
{
	assert(defaults && numPairs > 0);

	int sw = GetSystemMetrics(SM_CXSCREEN);
	int sh = GetSystemMetrics(SM_CYSCREEN);

	w = 0;
	h = 0;
	for (int i = 0; i < numPairs; ++i)
	{
		int newW = defaults[i * 2], newH = defaults[i * 2 + 1];

		if (w < newW && newW < sw && newH < sh)
		{
			w = newW;
			h = newH;
		}
	}
	assert(w > 0);
}

