#include "GameObj.h"
#include"Application.h"
void GameObj::Update()
{
	if (mVel.x != 0 || mVel.y != 0)
	{
		Vec2f pos{(mVel * Application::GetElapsedSecs() ) + mSprite.getPosition() };
		mSprite.setPosition(pos);
	}
}