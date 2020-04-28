#pragma once
#include<SFML/Graphics.hpp>
#include"Rectangle.h"
#include"Ball.h"
class Wall : public Rectangle
{
public:
	enum WallType { TOP, BOTTOM };	//identify where each wall is
	static const int MaxWalls = 2;
	Wall(Ball& _ball, WallType _type) : ball(_ball), type(_type) {}
	void Update(const float& deltaTime) override {
		if (ball.getGlobalBounds().intersects(getGlobalBounds())) {
			// collision detected
			if (type == TOP)
			{
			ball.SetVel(Vec2f(ball.GetVel().x > 0 ? GameData::ballSpeed : -GameData::ballSpeed, GameData::ballSpeed));
			}
			else
			{
				ball.SetVel(Vec2f(ball.GetVel().x > 0 ? GameData::ballSpeed : -GameData::ballSpeed, -GameData::ballSpeed));
			}
		}
	}
private:
	Ball& ball;
	WallType type;
};

