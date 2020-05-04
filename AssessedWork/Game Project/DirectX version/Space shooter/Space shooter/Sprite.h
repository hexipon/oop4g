#pragma once
#include "SpriteBatch.h"
#include "d3d.h"
#include"TextureCache.h"
#include"Animation.h"


class Sprite
{
private:
	ID3D11ShaderResourceView *pTex;
	d3d& _d3d;
	RECTF TexRect;
	DirectX::SimpleMath::Vector2 scale;
	const TextureCache::Data *TexData;
	DirectX::SimpleMath::Vector2 Pos;
	DirectX::SimpleMath::Vector2 Vel;
	float depth;
	DirectX::SimpleMath::Vector4 colour;
	float rotation;
	DirectX::SimpleMath::Vector2 origin;
	Animation Anim;

public:

	Sprite(d3d& d3d)
		:Pos(0, 0), Vel(0, 0),
		depth(0), TexRect{ 0,0,0,0 }, colour(1, 1, 1, 1),
		rotation(0), scale(1, 1), origin(0, 0), pTex(nullptr),
		_d3d(d3d), Anim(*this)
	{}
	Sprite(const Sprite& rhs)
		:_d3d(rhs._d3d), Anim(*this)
	{
		(*this) = rhs;
	}
	Sprite& operator=(const Sprite& rhs);

	void Draw(DirectX::SpriteBatch& batch);
	void SetTex(ID3D11ShaderResourceView& tex, const RECTF& texRect = RECTF{ 0,0,0,0 });
	void SetTexRect(const RECTF& texRect);
	void Scroll(float x, float y);
	const TextureCache::Data& GetTexData() const {
		return *TexData;
	}
	const ID3D11ShaderResourceView& GetTex() {
		return *pTex;
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
	const void setColour(DirectX::SimpleMath::Vector4 _colour) {
		colour = _colour;
	}
	DirectX::SimpleMath::Vector2 GetScreenSize() const {
		if (TexRect.right == 0)
			return scale * TexData->dim;
		return scale * DirectX::SimpleMath::Vector2(TexRect.right - TexRect.left, TexRect.bottom - TexRect.top);
	}
	DirectX::SimpleMath::Vector2 GetPosition() const {
		return Pos;
	}

	void SetFrame(int id);
	Animation& GetAnim() {
		return Anim;
	}
};

