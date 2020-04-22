#include "Asteroid.h"
void Asteroid::Init(d3d& _d3d)
{
	std::vector<RECTF> frames2;
	frames2.insert(frames2.begin(), 8 * 8, RECTF());
	const float ASS_SZ = 102;
	int c = 0;
	for (int y = 0; y < 8; ++y)
		for (int x = 0; x < 8; ++x)
			frames2[c++] = RECTF{ x*ASS_SZ,y*ASS_SZ,x*ASS_SZ + ASS_SZ,y*ASS_SZ + ASS_SZ };
	ID3D11ShaderResourceView* p = _d3d.GetCache().LoadTexture(&_d3d.GetDevice(), "asteroid.dds", "asteroid", true, &frames2);
	spr.SetTex(*p);
	spr.GetAnim().Init(0, 31, 15, true);
	spr.GetAnim().Play(true);
	spr.SetScale(DirectX::SimpleMath::Vector2(1.f, 1.f));
	active = false;
}

void Asteroid::Render(DirectX::SpriteBatch& batch)
{
	if (active)
		spr.Draw(batch);
}

void Asteroid::Update(float dTime)
{
	if (active)
	{

		spr.SetPosition(DirectX::SimpleMath::Vector2( spr.GetPosition().x - gameConstants::ASTEROID_SPEED * dTime, spr.GetPosition().y ));
		if (spr.GetPosition().x < 0 - spr.GetScreenSize().x)
			active = false;
		spr.GetAnim().Update(dTime);
		if (health <= 0)
		{
			health = 10;
			Score::Get().score += 10;
			active = false;
		}
	}
}

bool Asteroid::CheckCollision(Sprite& sprite) {
	DirectX::SimpleMath::Vector2 pos1 = DirectX::SimpleMath::Vector2(spr.GetPosition().x - (sprite.GetScreenSize().x/2) + (spr.GetScreenSize().x/2), spr.GetPosition().y);
	DirectX::SimpleMath::Vector2 pos2 = DirectX::SimpleMath::Vector2(sprite.GetPosition().x, sprite.GetPosition().y);
	
	return(((pos1.x - pos2.x)*(pos1.x - pos2.x) + (pos1.y - pos2.y)*(pos1.y - pos2.y)) < 3000);
}