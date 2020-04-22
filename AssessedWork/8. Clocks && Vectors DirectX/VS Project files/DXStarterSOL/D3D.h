#ifndef D3DH
#define D3DH

#include <vector>
#include <cassert>
#include <d3d11.h>
#include"SimpleMath.h"
#include "TexCache.h"
#include "WindowUtils.h"
#include "D3DUtil.h"


class MyD3D
{
public:
	bool InitDirect3D(void(*pOnResize)(int, int, MyD3D&));
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
	//see mpOnResize
	void OnResize(int sw, int sh, MyD3D& d3d) {
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
	bool mWindowed = false;
	ID3D11Device* mpd3dDevice = nullptr;
	ID3D11DeviceContext* mpd3dImmediateContext = nullptr;
	IDXGISwapChain* mpSwapChain = nullptr;
	ID3D11RenderTargetView* mpRenderTargetView = nullptr;
	ID3D11DepthStencilView* mpDepthStencilView = nullptr;
	D3D11_VIEWPORT mScreenViewport;
	void(*mpOnResize)(int, int, MyD3D&) = nullptr;

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




#endif
