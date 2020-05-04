#pragma once
#include"TextureCache.h"
#include"SpriteBatch.h"
#include"SpriteFont.h"
#include"d3d.h"
#include"FontCache.h"
class Text
{
private:
	d3d& _d3d;
	const DirectX::SpriteFont& font;
	DirectX::SimpleMath::Vector2 Pos;
	DirectX::SimpleMath::Vector4 colour;
	float rotation;
	DirectX::SimpleMath::Vector2 origin;
	DirectX::SimpleMath::Vector2 scale;
	std::string text="";
public:
	Text(d3d& d3d_, const std::string& fileName) : 
		_d3d(d3d_), font(FontCache::Get().LoadFont(fileName)),
	Pos(0,0), colour(1,1,1,1), rotation(0), origin(0,0), scale(1,1)
	{
	}
	const void Draw(DirectX::SpriteBatch& batch) {
		font.DrawString(&batch, text.c_str(), Pos, colour, rotation, origin, scale, DirectX::SpriteEffects::SpriteEffects_None, 0.f);
	}
	const void SetScale(const DirectX::SimpleMath::Vector2& s) {
		scale = s;
	}
	const void SetOrigin(const DirectX::SimpleMath::Vector2& o) {
		origin = o;
	}
	const void SetPosition(const DirectX::SimpleMath::Vector2& p) {
		Pos = p;
	}
	const void SetRotation(const float& r) {
		rotation = r;
	}
	const DirectX::SimpleMath::Vector2& GetScale() const {
		return scale;
	}
	const DirectX::SimpleMath::Vector2 GetPosition() const {
		return Pos;
	}
	const void SetColour(DirectX::SimpleMath::Vector4 _colour) {
		colour = _colour;
	}
	const void setString(const std::string string)
	{
		text = string;
	}
	const DirectX::SimpleMath::Vector2 getSize() {
		return font.MeasureString(text.c_str());
	}
	const DirectX::SimpleMath::Vector4 getGlobalBounds() {
		return DirectX::SimpleMath::Vector4(
			GetPosition().x, 
			GetPosition().y, 
			GetPosition().x + getSize().x, 
			GetPosition().y + getSize().y);
	}

};

