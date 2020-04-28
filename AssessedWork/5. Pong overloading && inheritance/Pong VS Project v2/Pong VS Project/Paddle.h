#pragma once
#include"Rectangle.h"
#include"gameData.h"
#include"Ball.h"
#include"Wall.h"
class Paddle : public Rectangle
{
public:
	Paddle(Ball& _ball, Wall(&_walls)[Wall::MaxWalls]) : ball(_ball), Walls(_walls) {}
	void Update(const float& deltaTime) override {
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
			for(auto& wall : Walls)
				if(wall.getGlobalBounds().intersects(getGlobalBounds()))
					SetPos(Vec2f(GetPos().x, GetPos().y - (GameData::paddleSpeed * deltaTime)));

			break;
		case Paddle::DOWN:
			SetPos(Vec2f(GetPos().x, GetPos().y - (GameData::paddleSpeed * deltaTime)));
			for (auto& wall : Walls)
				if (wall.getGlobalBounds().intersects(getGlobalBounds()))
					SetPos(Vec2f(GetPos().x, GetPos().y + (GameData::paddleSpeed * deltaTime)));
			break;
		case Paddle::NONE:
		default:
			break;
		}		
		if (ball.getGlobalBounds().intersects(getGlobalBounds())) {
			// collision detected
			const float newXVel = (player == 1 ? GameData::ballSpeed : -GameData::ballSpeed);
			if ((ball.GetPos().y + ball.getGlobalBounds().height / 2) > (GetPos().y + getGlobalBounds().height / 2))
			{
				ball.SetVel(Vec2f(newXVel, GameData::ballSpeed));
			}
			else
			{
				ball.SetVel(Vec2f(newXVel, -GameData::ballSpeed));
			}
		}
	}
	void setPlayerNum(const int playerNum)
	{
		player = playerNum;
	}
private:
	const enum movement {UP, DOWN, NONE};
	movement move;
	Ball& ball;
	Wall (&Walls)[Wall::MaxWalls];
	int player = 1; //default player 1
};

