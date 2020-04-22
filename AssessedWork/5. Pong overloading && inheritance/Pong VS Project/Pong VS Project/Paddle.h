#pragma once
#include"Rectangle.h"
#include"gameData.h"
#include"Ball.h"
#include"Wall.h"
class Paddle : public Rectangle
{
public:
	void Update(const float& deltaTime) {
		move = movement::NONE;
		if(player==1)
		{
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
				move = movement::UP;
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
				move = movement::DOWN;
		}
		if (player == 2)
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
				move = movement::UP;
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
				move = movement::DOWN;
		}
		switch (move)
		{
		case Paddle::UP:
			SetPos(Vec2f(GetPos().x, GetPos().y + (GameData::paddleSpeed * deltaTime)));
			for(auto wall : *Walls)
				if(wall.getGlobalBounds().intersects(getGlobalBounds()))
					SetPos(Vec2f(GetPos().x, GetPos().y - (GameData::paddleSpeed * deltaTime)));

			break;
		case Paddle::DOWN:
			SetPos(Vec2f(GetPos().x, GetPos().y - (GameData::paddleSpeed * deltaTime)));
			for (auto wall : *Walls)
				if (wall.getGlobalBounds().intersects(getGlobalBounds()))
					SetPos(Vec2f(GetPos().x, GetPos().y + (GameData::paddleSpeed * deltaTime)));
			break;
		case Paddle::NONE:
		default:
			break;
		}		
		if (ball->getGlobalBounds().intersects(getGlobalBounds())) {
			// collision detected
			ball->SetVel(Vec2f(-ball->GetVel().x, ball->GetVel().y));
		}
	}
	void setPlayerNum(const int playerNum)
	{
		player = playerNum;
	}
	void init(Ball& _ball, Wall (&_Walls)[Wall::MaxWalls]) { ball = &_ball; Walls = &_Walls; }
private:
	const enum movement {UP, DOWN, NONE};
	movement move;
	Ball* ball;
	Wall (*Walls)[Wall::MaxWalls];
	int player = 1; //default player 1
};

