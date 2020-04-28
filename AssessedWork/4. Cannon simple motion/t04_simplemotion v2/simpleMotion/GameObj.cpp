#include "GameObj.h"
#include"Application.h"
void GameObj::Update()
{
	if (Vel.x != 0 || Vel.y != 0)
	{
		Vec2f pos{(Vel * Application::GetElapsedSecs() ) + Sprite.getPosition() };
		Sprite.setPosition(pos);
	}
}