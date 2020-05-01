#pragma once
#include <string>
#include <vector>
#include <unordered_map>
#include <d3d11.h>
#include "D3DUtils.h"


struct RECTF
{
	float left, top, right, bottom;
	operator RECT() {
		return RECT{ (int)left,(int)top,(int)right,(int)bottom };
	}
};
class TextureCache
{
public:
	struct Data
	{
		Data() {}
		Data(const std::string& fName, ID3D11ShaderResourceView*p, const DirectX::SimpleMath::Vector2& _dim)
			: fileName(fName), pTex(p), dim(_dim)
		{
			frames.clear();
		}
		Data(const std::string& fName, ID3D11ShaderResourceView*p, const DirectX::SimpleMath::Vector2& _dim, const std::vector<RECTF> *_frames)
			:fileName(fName), pTex(p), dim(_dim)

		{
			if (_frames)
				frames = *_frames;
		}
		std::string fileName;
		ID3D11ShaderResourceView* pTex = nullptr;
		DirectX::SimpleMath::Vector2 dim;
		std::vector<RECTF> frames;
	};

	void Release();
	ID3D11ShaderResourceView* LoadTexture(ID3D11Device*pDevice, const std::string& fileName, const std::string& texName = "", bool appendPath = true, const std::vector<RECTF> *_frames = nullptr);
	void SetAssetPath(const std::string& path) {
		mAssetPath = path;
	}
	Data& Get(const std::string& texName) {
		return mCache.at(texName);
	}
	const Data& Get(ID3D11ShaderResourceView *pTex);

private:
	DirectX::SimpleMath::Vector2 GetDimensions(ID3D11ShaderResourceView* pTex);
	typedef std::unordered_map<std::string, Data> MyMap;
	MyMap mCache;

	std::string mAssetPath;
};

