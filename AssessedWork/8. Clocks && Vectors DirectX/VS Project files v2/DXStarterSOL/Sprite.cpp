#include "Sprite.h"
#include "CommonStates.h"

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
void Sprite::SetTex(ID3D11ShaderResourceView& tex, const RECTF& texRect)
{
	pTex = &tex;
	TexRect = texRect;
	TexData = &_D3D.GetCache().Get(pTex);

	if (TexRect.left == TexRect.right && TexRect.top == TexRect.bottom)
	{
		SetTexRect(RECTF{ 0,0,TexData->dim.x,TexData->dim.y });
	}
}