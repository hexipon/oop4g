#pragma once
#include <windows.h>
#include <string>
#include <sstream>
#include <assert.h>

class d3d;

class WindowUtils
{
public:
	WindowUtils(WindowUtils const&) = delete;
	void operator=(WindowUtils const&) = delete;
	static WindowUtils& Get() { static WindowUtils instance; return instance;}
	static LRESULT DefaultMssgHandler(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
	{
		return WindowUtils::Get().RealDefaultMssgHandler(hwnd, msg, wParam, lParam);
	}
	bool InitMainWindow(int width, int height, HINSTANCE hInstance, const std::string& appName, WNDPROC mssgHandler, bool centred = true);
	void SetD3D(d3d& d3d) {
		assert(mpMyD3D == nullptr);
		mpMyD3D = &d3d;
	}
	//wrap your game in one function call if using basic functions
	int Run(void(*pUpdate)(float), void(*pRender)(float));
	//if you are using class member fucntions then try this instead
	bool BeginLoop(bool& canUpdateRender);
	float EndLoop(bool didUpdateRender);
	//or even rework the Run function using std::function and lamdas to wrap the member function with a this pointer

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
		//all windows apps have these handles
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

	WindowUtils()
		:mpMyD3D(nullptr)
	{}
	LRESULT RealDefaultMssgHandler(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
};