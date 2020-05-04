#pragma once
#include<vector>
#include"d3d.h"
#include"SpriteFont.h"
#include"WindowUtils.h"
#include"Singleton.h"

class Font
{
private:
	const std::wstring FileName;
	DirectX::SpriteFont _Font;
public:
	Font(const std::wstring _string) :
	FileName(_string),
_Font(DirectX::SpriteFont(&WindowUtils::Get().GetD3D().GetDevice(), FileName.c_str()))
	{
	}
	const std::string GetFileName() {
		const std::string stringFileName(FileName.begin(), FileName.end());
		return stringFileName;
	}
	const DirectX::SpriteFont& GetFont() {
		return _Font;
	}

};

class FontCache : public Singleton<FontCache> {
private:
	std::vector<Font> _FontCache;
	std::string AssetPath;
public:
	~FontCache() {
		_FontCache.clear();
	}
	const DirectX::SpriteFont& LoadFont(const std::string& fileName) {

		std::string filepath = std::string(AssetPath + fileName);
		const std::string *pPath = &filepath;
		std::wstring ws(pPath->begin(), pPath->end());

		for (auto& font : _FontCache)
			if ((AssetPath + fileName) == font.GetFileName())
				return font.GetFont();
		_FontCache.push_back(Font(ws.c_str()));
		return _FontCache.back().GetFont();
	}	
	void SetAssetPath(const std::string& path) {
		AssetPath = path;
	}

};