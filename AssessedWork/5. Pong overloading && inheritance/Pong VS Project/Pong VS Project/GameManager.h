#pragma once
#include<deque>
#include"State.h"
#include"Menu.h"
#include"Game.h"
#include"gameData.h"
class GameManager
{
public:
	static GameManager& Instance() { static GameManager gameManager; return gameManager; }
	const void Init();
	const enum stateNames
	{
		Menu,
		Game,
		Player1Wins,
		Player2Wins
	};
	const void changeState(const stateNames& newState);
private:
	GameManager() { windowSetup(); changeState(stateNames::Menu); }
	~GameManager();
	stateNames currentState;
	sf::RenderWindow window;
	sf::Event sfEvent;
	sf::Clock clock;
	float deltaTime;
	std::deque<State*> states;
	const void windowSetup();
	const void sfEventUpdate();
	const void deltaTimeUpdate();
	const void update();
	const void render();
};

