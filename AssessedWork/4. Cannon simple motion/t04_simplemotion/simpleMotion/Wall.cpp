#include "Wall.h"
void Wall::Update()
{
	//add ball collision code here
	const Vec2f rect1 = ball->GetPos();
	const Vec2f rect2 = GetPos();
	const Vec2f rect1scale = ball->GetScale();
	const Vec2f rect2scale = GetScale();
	if(ball->getGlobalBounds().intersects(getGlobalBounds())){
		// collision detected

		if (mType == WallType::TOP || mType == WallType::BOTTOM)
			ball->SetVel(Vec2f(ball->GetVel().x, -ball->GetVel().y));
		if (mType == WallType::LEFT || mType == WallType::RIGHT)
			ball->SetVel(Vec2f(-ball->GetVel().x, ball->GetVel().y));
	}

}
