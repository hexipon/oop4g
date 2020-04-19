#include "Sprite.h"
#include "CommonStates.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

Sprite& Sprite::operator=(const Sprite& rhs) {
	mPos = rhs.mPos;
	mVel = rhs.mVel;
	depth = rhs.depth;
	mTexRect = rhs.mTexRect;
	colour = rhs.colour;
	rotation = rhs.rotation;
	scale = rhs.scale;
	origin = rhs.origin;
	mpTex = rhs.mpTex;
	return *this;
}
void Sprite::Draw(SpriteBatch& batch)
{
	batch.Draw(mpTex, mPos, &(RECT)mTexRect, colour, rotation, origin, scale, DirectX::SpriteEffects::SpriteEffects_None, depth);
}
void Sprite::SetTex(ID3D11ShaderResourceView& tex, const RECTF& texRect)
{
	mpTex = &tex;
	mTexRect = texRect;
	if (mTexRect.left == mTexRect.right && mTexRect.top == mTexRect.bottom)
	{
		TexCache::Data& data = mD3D.GetCache().Get(mpTex);
		SetTexRect(RECTF{ 0,0,data.dim.x,data.dim.y });
	}
}
void Sprite::SetTexRect(const RECTF& texRect) {
	mTexRect = texRect;
}

