#pragma once
#include <vector>
#include <cassert>
#include <d3d11.h>
#include"SimpleMath.h"
#include "TexCache.h"
#include "WinUtil.h"
#include "D3DUtil.h"

//stuck these here so gamepad and mousekeys class has access to them 
#define VK_NUMPAD_ENTER 0xF0		//these three are very naughty
#define VK_LALT			0xF1		//they are actually some oem
#define VK_RALT			0xF2		//keys ATTN/FINISH/COPY - but lets pinch them :)


#define VK_0	0x30
#define VK_1	0x31
#define VK_2	0x32
#define VK_3	0x33
#define VK_4	0x34
#define VK_5	0x35
#define VK_6	0x36
#define VK_7	0x37
#define VK_8	0x38
#define VK_9	0x39
//these codes match ascii
#define VK_A	0x41
#define VK_B	0x42
#define VK_C	0x43
#define VK_D	0x44
#define VK_E	0x45
#define VK_F	0x46
#define VK_G	0x47
#define VK_H	0x48
#define VK_I	0x49
#define VK_J	0x4a
#define VK_K	0x4b
#define VK_L	0x4c
#define VK_M	0x4d
#define VK_N	0x4e
#define VK_O	0x4f
#define VK_P	0x50
#define VK_Q	0x51
#define VK_R	0x52
#define VK_S	0x53
#define VK_T	0x54
#define VK_U	0x55
#define VK_V	0x56
#define VK_W	0x57
#define VK_X	0x58
#define VK_Y	0x59
#define VK_Z	0x5a

class d3d
{
public:
	bool InitDirect3D(void(*pOnResize)(int, int, d3d&));
	void OnResize_Default(int clientWidth, int clientHeight);
	void ReleaseD3D(bool extraReporting = true);
	float GetAspectRatio();
	void BeginRender(const DirectX::SimpleMath::Vector4& colour);
	void EndRender();
	ID3D11Device& GetDevice() {
		assert(mpd3dDevice);
		return *mpd3dDevice;
	}
	ID3D11DeviceContext& GetDeviceCtx() {
		assert(mpd3dImmediateContext);
		return *mpd3dImmediateContext;
	}
	bool GetDeviceReady() const {
		return mpd3dDevice != nullptr;
	}
	void OnResize(int sw, int sh, d3d& d3d) {
		assert(mpOnResize);
		mpOnResize(sw, sh, d3d);
	}
	TexCache& GetCache() { return mTexCache; }
	ID3D11SamplerState& GetWrapSampler() {
		assert(mpWrapSampler);
		return *mpWrapSampler;
	}

private:
	TexCache mTexCache;
	D3D_DRIVER_TYPE md3dDriverType = D3D_DRIVER_TYPE_UNKNOWN;
	UINT m4xMsaaQuality = 0;
	ID3D11Texture2D* mpDepthStencilBuffer = nullptr;
	bool mEnable4xMsaa = true;
	bool mWindowed = true;
	ID3D11Device* mpd3dDevice = nullptr;
	ID3D11DeviceContext* mpd3dImmediateContext = nullptr;
	IDXGISwapChain* mpSwapChain = nullptr;
	ID3D11RenderTargetView* mpRenderTargetView = nullptr;
	ID3D11DepthStencilView* mpDepthStencilView = nullptr;
	D3D11_VIEWPORT mScreenViewport;
	void(*mpOnResize)(int, int, d3d&) = nullptr;
	ID3D11SamplerState* mpWrapSampler = nullptr;
	void CreateD3D(D3D_FEATURE_LEVEL desiredFeatureLevel = D3D_FEATURE_LEVEL_11_0);
	void ResizeSwapChain(int screenWidth, int screenHeight);
	void CreateDepthStencilDescription(D3D11_TEXTURE2D_DESC& dsd, int screenWidth, int screenHeight, bool msaa4X, int maxQuality);
	void CreateDepthStencilBufferAndView(D3D11_TEXTURE2D_DESC& dsd);
	void BindRenderTargetViewAndDepthStencilView();
	void SetViewportDimensions(int screenWidth, int screenHeight);
	void CheckMultiSamplingSupport(UINT& quality4xMsaa);
	void CreateSwapChainDescription(DXGI_SWAP_CHAIN_DESC& sd, HWND hMainWnd, bool windowed, int screenWidth, int screenHeight);
	void CreateSwapChain(DXGI_SWAP_CHAIN_DESC& sd);

	void CreateWrapSampler(ID3D11SamplerState* &pSampler);

};


