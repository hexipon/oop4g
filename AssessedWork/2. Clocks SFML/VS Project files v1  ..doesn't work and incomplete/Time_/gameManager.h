#pragma once
class gameManager
{
private:
	sf::RenderWindow window;
	std::stack<AnClock> anClocks;
	sf::Event sfEvent;
	//sf::Clock clock;
	sf::Text topText;
	sf::Text bottomText;
	DigClock digClock;
	sf::Font digFont;
	sf::Font textFont;
	float deltaTime;

	ClockTime correctTime;

	void winSetup();
	void sfEventUpdate();
	void deltaTimeUpdate();
	void update();
	void render();

	int randTime() const;

public:
	gameManager();
};

