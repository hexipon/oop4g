#pragma once
#include <windows.h>
#include <string>
#include <sstream>
#include <assert.h>

class d3d;

class WinUtil
{
public:
	WinUtil(WinUtil const&) = delete;
	void operator=(WinUtil const&) = delete;
	static WinUtil& Get()
	{
		static WinUtil instance;
		return instance;
	}
	static LRESULT DefaultMssgHandler(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
	{
		return WinUtil::Get().RealDefaultMssgHandler(hwnd, msg, wParam, lParam);
	}
	bool InitMainWindow(int width, int height, HINSTANCE hInstance, const std::string& appName, WNDPROC mssgHandler, bool centred = true);
	void SetD3D(d3d& d3d) {
		assert(mpMyD3D == nullptr);
		mpMyD3D = &d3d;
	}
	//int Run(void(*pUpdate)(float), void(*pRender)(float));
	bool BeginLoop(bool& canUpdateRender);
	float EndLoop(bool didUpdateRender);

	HINSTANCE GetAppInst();
	HWND GetMainWnd();
	void GetClientExtents(int& width, int& height) const;
	int GetClientWidth() const {
		return mWinData.clientWidth;
	}
	int GetClientHeight() const {
		return mWinData.clientHeight;
	}
	void ChooseRes(int& w, int& h, int defaults[], int numPairs);

private:
	struct WinData
	{
		HINSTANCE hAppInst = 0;
		HWND      hMainWnd = 0;
		bool      appPaused = false;
		bool      minimized = false;
		bool      maximized = false;
		bool      resizing = false;
		std::string mainWndCaption;
		int clientWidth;
		int clientHeight;
	};
	WinData mWinData;
	d3d *mpMyD3D;

	WinUtil()
		:mpMyD3D(nullptr)
	{}
	LRESULT RealDefaultMssgHandler(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
};