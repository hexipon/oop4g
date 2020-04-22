#include "Sprite.h"

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
	Tex = rhs.Tex;
	return *this;
}
void Sprite::Draw(SpriteBatch& batch)
{
	batch.Draw(Tex, Pos, &(RECT)TexRect, colour, rotation, origin, scale, DirectX::SpriteEffects::SpriteEffects_None, depth);
}
void Sprite::SetTex(ID3D11ShaderResourceView& tex, const RECTF& texRect)
{
	Tex = &tex;
	TexRect = texRect;
	TexData = &_D3D.GetCache().Get(Tex);

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