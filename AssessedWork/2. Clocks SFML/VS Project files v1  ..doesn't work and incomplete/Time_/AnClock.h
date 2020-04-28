#pragma once
class AnClock
{
private:
	sf::RectangleShape bigHand;
	sf::RectangleShape smallHand;
	sf::Sprite baseImg;
	sf::Texture tex;
	sf::Text clockNum;
	ClockTime AnTime;
	const sf::Vector2f position;
	void setHandRotations();
public:
	AnClock();
	//void setNewTime(ClockTime*);
	void update();
	void render(sf::RenderWindow&);
};

