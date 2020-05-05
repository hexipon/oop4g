#include "Bullet.h"


void Bullet::Render()
{
	spr.Draw(_spritebatch);
}

void Bullet::Update()
{
	spr.SetPosition(DirectX::SimpleMath::Vector2(spr.GetPosition().x + ((deltaTime * direction*MISSILE_SPEED*(gameData::Get().WindowSize.x / gameData::Get().MaxWindowSize.x)) + (deltaTime* aditionalSpeed)/2) , spr.GetPosition().y));
	if (spr.GetPosition().x > WindowUtils::Get().GetClientWidth())
		active = false;
	spr.GetAnim().Update(deltaTime);
	if (spr.GetPosition().x > gameData::Get().WindowSize.x || spr.GetPosition().x < 0)
	{
		active = false;
	
	}

}

const bool Bullet::CheckCollision(Sprite & sprite)
{
	DirectX::SimpleMath::Vector2 pos1 = DirectX::SimpleMath::Vector2(spr.GetPosition().x - (sprite.GetScreenSize().x / 2) + (spr.GetScreenSize().x / 2),
		spr.GetPosition().y + spr.GetScreenSize().y / 2);
	DirectX::SimpleMath::Vector2 pos2 = DirectX::SimpleMath::Vector2(sprite.GetPosition().x,
		sprite.GetPosition().y + sprite.GetScreenSize().y / 2);

	return(((pos1.x - pos2.x)*(pos1.x - pos2.x) + (pos1.y - pos2.y)*(pos1.y - pos2.y)) <
		(sprite.GetScreenSize().x / 2)*(sprite.GetScreenSize().x / 2) + (spr.GetScreenSize().x / 2)*(spr.GetScreenSize().x / 2));
}
