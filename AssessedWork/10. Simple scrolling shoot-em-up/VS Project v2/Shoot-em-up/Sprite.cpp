#include "Sprite.h"
#include"Animation.h"
using namespace DirectX;
using namespace DirectX::SimpleMath;

Sprite& Sprite::operator=(const Sprite& rhs) {
	Pos = rhs.Pos;
	Vel = rhs.Vel;
	depth = rhs.depth;
	TexRect = rhs.TexRect;
	colour = rhs.colour;
	rotation = rhs.rotation;
	scale = rhs.scale;
	origin = rhs.origin;
	pTex = rhs.pTex;
	return *this;
}
void Sprite::Draw(SpriteBatch& batch)
{
	batch.Draw(pTex, Pos, &(RECT)TexRect, colour, rotation, origin, scale, DirectX::SpriteEffects::SpriteEffects_None, depth);
}
void Sprite::SetTex(ID3D11ShaderResourceView& tex, const RECTF& texRect)
{
	pTex = &tex;
	TexRect = texRect;
	TexData = &_d3d.GetCache().Get(pTex);

	if (TexRect.left == TexRect.right && TexRect.top == TexRect.bottom)
	{
		SetTexRect(RECTF{ 0,0,TexData->dim.x,TexData->dim.y });
	}
}
void Sprite::SetTexRect(const RECTF& texRect) {
	TexRect = texRect;
}
void Sprite::Scroll(float x, float y) {
	TexRect.left += x;
	TexRect.right += x;
	TexRect.top += y;
	TexRect.bottom += y;
}

void Sprite::SetFrame(int id)
{
	const TextureCache::Data& data = _d3d.GetCache().Get(pTex);
	SetTexRect(data.frames.at(id));
}
