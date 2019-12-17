#pragma once
class DigClock
{
private:
	ClockTime& DiTime;
	sf::Texture tex;
	sf::Sprite baseImg;
	sf::Text timeT;
	const sf::Vector2f position;
public:
	DigClock(ClockTime& DiTime, const sf::Vector2f pos) : DiTime(DiTime), position(pos) {};
	void init(const sf::Font&);
	void update();
	void render(sf::RenderWindow&);
};

