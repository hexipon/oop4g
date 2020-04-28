#pragma once
#include<SFML/Graphics.hpp>
#include"Time.h"
class AnClock
{
private:
	sf::RectangleShape bigHand;
	sf::RectangleShape smallHand;
	//sf::RectangleShape secondsHand;
	sf::Sprite baseImg;
	sf::Font font;
	sf::Texture tex;
	sf::Text clockNum;
	Time AnTime;
	const sf::Vector2f position;

public:
	AnClock(const int i, const sf::Vector2f pos);
	void setNewTime(const Time&);
	void setNewTime();
	void update(float& deltaTime);
	void render(sf::RenderWindow&);
	Time getTime();
};

