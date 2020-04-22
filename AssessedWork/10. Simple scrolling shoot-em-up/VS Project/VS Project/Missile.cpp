#include "Missile.h"
const RECTF missileAnim[]{
	{ 0,  0, 53, 48},
	{ 54, 0, 107, 48 },
	{ 108, 0, 161, 48 },
	{ 162, 0, 220, 48 },
};

void Missile::Init(d3d & _d3d)
{
	std::vector<RECTF> frames3(missileAnim, missileAnim + sizeof(missileAnim) / sizeof(missileAnim[0]));
	ID3D11ShaderResourceView* p = _d3d.GetCache().LoadTexture(&_d3d.GetDevice(), "missile.dds", "missile", true, &frames3);

	spr.SetTex(*p);
	spr.GetAnim().Init(0, 3, 15, true);
	spr.SetScale(DirectX::SimpleMath::Vector2(0.5f, 0.5f));
	active = false;
}

void Missile::Render(DirectX::SpriteBatch & batch)
{
	if (active)
		spr.Draw(batch);
}

void Missile::Update(float dTime)
{
	if (active)
	{
	spr.GetAnim().Play(true);
		spr.SetPosition(DirectX::SimpleMath::Vector2(spr.GetPosition().x + MISSILE_SPEED * dTime, spr.GetPosition().y));
		if (spr.GetPosition().x > WindowUtils::Get().GetClientWidth())
			active = false;
		spr.GetAnim().Update(dTime);
	}
}

bool Missile::CheckCollision(Sprite & sprite)
{
	DirectX::SimpleMath::Vector2 pos1 = DirectX::SimpleMath::Vector2(spr.GetPosition().x - (sprite.GetScreenSize().x / 2) + (spr.GetScreenSize().x / 2), spr.GetPosition().y);
	DirectX::SimpleMath::Vector2 pos2 = DirectX::SimpleMath::Vector2(sprite.GetPosition().x, sprite.GetPosition().y);

	return(((pos1.x - pos2.x)*(pos1.x - pos2.x) + (pos1.y - pos2.y)*(pos1.y - pos2.y)) < (sprite.GetScreenSize().x / 2)*(sprite.GetScreenSize().x / 2)+ (spr.GetScreenSize().x / 2)*(spr.GetScreenSize().x / 2));
}
