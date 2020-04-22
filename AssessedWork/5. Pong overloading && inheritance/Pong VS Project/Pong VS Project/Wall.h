#pragma once
#include<SFML/Graphics.hpp>
#include"Rectangle.h"
#include"Ball.h"
class Wall : public Rectangle
{
public:
	enum WallType { TOP, BOTTOM };	//identify where each wall is
	static const int MaxWalls = 2;
	void Update(const float& deltaTime) {
		if (ball->getGlobalBounds().intersects(getGlobalBounds())) {
			// collision detected
			ball->SetVel(Vec2f(ball->GetVel().x, -ball->GetVel().y));
		}
	}
	const void init(Ball& _ball) {
		ball = &_ball;
	}
private:
	Ball* ball;
};

