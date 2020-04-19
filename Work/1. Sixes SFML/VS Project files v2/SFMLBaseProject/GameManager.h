#pragma once
#include"stdafx.h"
#include"Game.h"
#include"State.h"
#include"NameInput.h"
#include"End.h"
class GameManager
{
private:
	sf::RenderWindow window;
	std::stack<State*> states;
	std::vector<sf::Text> lines;
	sf::Font font;
	sf::String playerName;
	sf::String numInput;
	sf::Event sfEvent;
	int score;
	void fontSetup();
	void windowSetup();
	void sfEventUpdate();
	void update();
	void render();
	void startState();
	void nextScene(const int& sceneNum);
	void numScene();
	void sortLines();
	void rollDice();
public:
	GameManager();
	void start();
};

