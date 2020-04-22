#pragma once
#include <string>
#include <vector>
#include <unordered_map>
#include <d3d11.h>
#include"SimpleMath.h"


class TexCache
{
public:
	struct Data
	{
		Data() {}
		Data(const std::string& fName, ID3D11ShaderResourceView*p, const DirectX::SimpleMath::Vector2& dim)
			: fileName(fName), Tex(p), dim(dim)
		{}
		std::string fileName;
		ID3D11ShaderResourceView* Tex = nullptr;
		DirectX::SimpleMath::Vector2 dim;
	};

	void Release();
	ID3D11ShaderResourceView* LoadTexture(ID3D11Device*pDevice, const std::string& fileName, const std::string& texName = "", bool appendPath = true);
	void SetAssetPath(const std::string& path) {
		mAssetPath = path;
	}
	Data& Get(const std::string& texName) {
		return mCache.at(texName);
	}
	Data& Get(ID3D11ShaderResourceView *pTex);

private:
	DirectX::SimpleMath::Vector2 GetDimensions(ID3D11ShaderResourceView* pTex);
	typedef std::unordered_map<std::string, Data> MyMap;
	MyMap mCache;

	std::string mAssetPath;
};


