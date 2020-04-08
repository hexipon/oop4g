#pragma once
#include<SFML/Graphics.hpp>
#include<vector>
#include"Time.h"
#include"DigClock.h"
#include"AnClock.h"
class gameManager
{
public:
	gameManager();
	void Init();
private:
	enum State {Playing, Limbo};
	State state = State::Playing;
	sf::RenderWindow window;
	AnClock *anClocks [3];
	sf::Event sfEvent;
	sf::Clock clock;
	sf::Text topText;
	sf::Text bottomText;
	DigClock digClock;
	sf::Font digFont;
	sf::Font textFont;
	float deltaTime;

	Time correctTime;

	void winSetup();
	void sfEventUpdate();
	void update();
	void render();

	void setClocks();

	void checkIfCorrect(const int code);
};

