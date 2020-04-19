#pragma once
#include "SpriteBatch.h"
#include "D3D.h"

/*
Used to specify areas within sprites for rendering
*/
struct RECTF
{
	float left, top, right, bottom;
	operator RECT() {
		return RECT{ (int)left,(int)top,(int)right,(int)bottom };
	}
};

/*
Gather together everything needed to render 2D sprites
capable of moving
*/
class Sprite
{
private:
	ID3D11ShaderResourceView *mpTex;		//texture
	MyD3D& mD3D;							//reference to main D3D system
	DirectX::SimpleMath::Vector2 mPos;		//position
	DirectX::SimpleMath::Vector2 mVel;		//velocity
	float depth;							//for sorting
	RECTF mTexRect;							//area of texture to use
	DirectX::SimpleMath::Vector4 colour;	//tint colour
	float rotation;							//radians
	DirectX::SimpleMath::Vector2 scale;		//size
	DirectX::SimpleMath::Vector2 origin;	//default is top left corner

public:

	Sprite(MyD3D& d3d)
		:mPos(0, 0), mVel(0, 0),
		depth(0), mTexRect{ 0,0,0,0 }, colour(1, 1, 1, 1),
		rotation(0), scale(1, 1), origin(0, 0), mpTex(nullptr),
		mD3D(d3d)
	{}
	Sprite(const Sprite& rhs)
		:mD3D(rhs.mD3D)
	{
		(*this) = rhs;
	}
	Sprite& operator=(const Sprite& rhs);
	//needs to be between begin/end pairs for main render and sprite batch
	void Draw(DirectX::SpriteBatch& batch);
	//by default it renders the whole texture
	void SetTex(ID3D11ShaderResourceView& tex, const RECTF& texRect = RECTF{ 0,0,0,0 });
	//change the area rendered
	void SetTexRect(const RECTF& texRect);
	//getters and setters - more needed
	void SetPos(const DirectX::SimpleMath::Vector2& pos) {
		mPos = pos;
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


