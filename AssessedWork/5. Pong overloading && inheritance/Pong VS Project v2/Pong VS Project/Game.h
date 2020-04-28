#pragma once
#include"State.h"
#include"Paddle.h"
#include"Score.h"
#include"Wall.h"
#include"Vec2f.h"
#include"gameData.h"
#include"Score.h"
#include"Text.h"
class _Game : public State
{
private:
	const enum PlayState{ ballOnPaddle, playing};
	bool ballOnPlayer1 = true;
	PlayState playState = PlayState::ballOnPaddle;
	Wall Walls[Wall::MaxWalls];
	Paddle player1;
	Paddle player2;
	Ball ball;
	Text text;
	int round = 0;
public:
	_Game(sf::RenderWindow& _window, float& _deltaTime);
	void updateInput(sf::Event& event) override;
	void update() override;
	void render() override;
};

