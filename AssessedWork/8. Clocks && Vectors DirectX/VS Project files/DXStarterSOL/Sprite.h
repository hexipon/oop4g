#pragma once
#include "SpriteBatch.h"
#include "D3D.h"

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
	ID3D11ShaderResourceView *pTex;		
	MyD3D& _D3D;							
	DirectX::SimpleMath::Vector2 Pos;		
	DirectX::SimpleMath::Vector2 Vel;		
	float depth;							
	RECTF TexRect;							
	DirectX::SimpleMath::Vector4 colour;	
	float rotation;							
	DirectX::SimpleMath::Vector2 scale;		
	DirectX::SimpleMath::Vector2 origin;	

public:

	Sprite(MyD3D& d3d)
		:Pos(0, 0), Vel(0, 0),
		depth(0), TexRect{ 0,0,0,0 }, colour(1, 1, 1, 1),
		rotation(0), scale(1, 1), origin(0, 0), pTex(nullptr),
		_D3D(d3d)
	{}
	Sprite(const Sprite& rhs)
		:_D3D(rhs._D3D)
	{
		(*this) = rhs;
	}
	Sprite& operator=(const Sprite& rhs);
	void Draw(DirectX::SpriteBatch& batch) {
		batch.Draw(pTex, Pos, &(RECT)TexRect, colour, rotation, origin, scale, DirectX::SpriteEffects::SpriteEffects_None, depth);
	}
	void SetTex(ID3D11ShaderResourceView& tex, const RECTF& texRect = RECTF{ 0,0,0,0 });
	void SetTexRect(const RECTF& texRect) {
		TexRect = texRect;
	}
	void SetPos(const DirectX::SimpleMath::Vector2& pos) {
		Pos = pos;
	}
	void SetScale(const DirectX::SimpleMath::Vector2& s) {
		scale = s;
	}
	void SetOrigin(const DirectX::SimpleMath::Vector2& o) {
		origin = o;
	}
	void setRotation(const float& r) {
		rotation = r;
	}
	const DirectX::SimpleMath::Vector2& GetScale() const {
		return scale;
	}
};


