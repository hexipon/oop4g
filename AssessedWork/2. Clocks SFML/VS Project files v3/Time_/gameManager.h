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
	~gameManager()
	{
		for (auto * clock : anClocks)
		{
			delete clock;
			clock = nullptr;
		}
	}

	void Init();
private:
	const enum selectedClock { CLOCK1, CLOCK2, CLOCK3 };
	static const int Max_Clock = 3;
	enum State {Playing, Limbo};
	State state = State::Playing;
	sf::RenderWindow window;
	AnClock *anClocks [Max_Clock];
	sf::Event sfEvent;
	sf::Clock clock;
	sf::Text topText;
	sf::Text bottomText;
	sf::Font textFont;
	DigClock digClock;
	float deltaTime;

	Time correctTime;

	void winSetup();
	void sfEventUpdate();
	void update();
	void render();

	void setClocks();

	void checkIfCorrect(const int code);
};

