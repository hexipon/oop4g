#pragma once
#include "SpriteBatch.h"
#include "d3d.h"
//handy rectangle definer
struct RECTF
{
	float left, top, right, bottom;
	operator RECT() {
		return RECT{ (int)left,(int)top,(int)right,(int)bottom };
	}
};

class Sprite
{
private:
	ID3D11ShaderResourceView *Tex;
	d3d& _D3D;
	RECTF TexRect;
	DirectX::SimpleMath::Vector2 scale;
	const TexCache::Data *TexData;
	DirectX::SimpleMath::Vector2 Pos;
	DirectX::SimpleMath::Vector2 Vel;
	float depth;
	DirectX::SimpleMath::Vector4 colour;
	float rotation;
	DirectX::SimpleMath::Vector2 origin;

public:

	Sprite(d3d& d3d)
		:Pos(0, 0), Vel(0, 0),
		depth(0), TexRect{ 0,0,0,0 }, colour(1, 1, 1, 1),
		rotation(0), scale(1, 1), origin(0, 0), Tex(nullptr),
		_D3D(d3d)
	{}
	Sprite(const Sprite& rhs)
		:_D3D(rhs._D3D)
	{
		(*this) = rhs;
	}
	Sprite& operator=(const Sprite& rhs);
	void Draw(DirectX::SpriteBatch& batch);
	void SetTex(ID3D11ShaderResourceView& tex, const RECTF& texRect = RECTF{ 0,0,0,0 });
	void SetTexRect(const RECTF& texRect);
	void Scroll(float x, float y);
	const TexCache::Data& GetTexData() const {
		return *TexData;
	}
	ID3D11ShaderResourceView& GetTex() {
		return *Tex;
	}
	void SetScale(const DirectX::SimpleMath::Vector2& s) {
		scale = s;
	}
	void SetOrigin(const DirectX::SimpleMath::Vector2& o) {
		origin = o;
	}
	void SetPosition(const DirectX::SimpleMath::Vector2& p) {
		Pos = p;
	}
	void SetRotation(const float& r) {
		rotation = r;
	}
	const DirectX::SimpleMath::Vector2& GetScale() const {
		return scale;
	}
	DirectX::SimpleMath::Vector2 GetScreenSize() const {
		return scale * TexData->dim;
	}
	DirectX::SimpleMath::Vector2 GetPosition() const {
		return Pos;
	}
};

