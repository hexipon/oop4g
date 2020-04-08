#pragma once
#include<SFML/Graphics.hpp>
#include"Time.h"
class DigClock
{
private:
	Time& DiTime;
	sf::Texture tex;
	sf::Sprite baseImg;
	sf::Text timeT;
	const sf::Vector2f position;
public:
	DigClock(Time& DiTime, const sf::Vector2f pos) : DiTime(DiTime), position(pos) {};
	void init(const sf::Font&);
	void update(float& deltaTime);
	void render(sf::RenderWindow&);
};

