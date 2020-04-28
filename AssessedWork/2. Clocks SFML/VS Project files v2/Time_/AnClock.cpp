#include "AnClock.h"

AnClock::AnClock(const int i, const sf::Vector2f pos) : position(pos)
{
	if (!font.loadFromFile("Retro.ttf"))
		throw("cannot find digital clock text file");
	clockNum.setString(std::to_string(i));
	if (!tex.loadFromFile("clock_face.png"))
		throw("Error loading digital clock texture!");
	baseImg.setTexture(tex);
	baseImg.setPosition(sf::Vector2f(position.x + baseImg.getGlobalBounds().width / 2, position.y + baseImg.getGlobalBounds().height / 2));
	baseImg.setScale(0.5, 0.5);
	clockNum.setFont(font);
	clockNum.setPosition(baseImg.getPosition());
	clockNum.setLetterSpacing(1);
	clockNum.setScale(1, 1);


	//secondsHand.setFillColor(sf::Color::Red);
	//secondsHand.setSize(sf::Vector2f(2.5, 95));
	//secondsHand.setOrigin(sf::Vector2f(secondsHand.getOrigin().x + (secondsHand.getGlobalBounds().width/2), secondsHand.getOrigin().y));
	//secondsHand.setPosition(sf::Vector2f(baseImg.getPosition().x + (baseImg.getGlobalBounds().width / 2), baseImg.getPosition().y + (baseImg.getGlobalBounds().height / 2)));
	//secondsHand.setScale(1, 1);
	//secondsHand.setRotation(180);

	smallHand.setFillColor(sf::Color::Blue);
	smallHand.setSize(sf::Vector2f(3, 55));
	smallHand.setOrigin(sf::Vector2f(smallHand.getOrigin().x + (smallHand.getGlobalBounds().width/2 ), smallHand.getOrigin().y));
	smallHand.setPosition(sf::Vector2f(baseImg.getPosition().x + (baseImg.getGlobalBounds().width / 2), baseImg.getPosition().y + (baseImg.getGlobalBounds().height / 2)));
	smallHand.setScale(1, 1);
	smallHand.setRotation(180);

	bigHand.setFillColor(sf::Color::Black);
	bigHand.setSize(sf::Vector2f(5, 95));
	bigHand.setOrigin(sf::Vector2f(bigHand.getOrigin().x + (bigHand.getGlobalBounds().width/2 ), bigHand.getOrigin().y));
	bigHand.setPosition(sf::Vector2f(baseImg.getPosition().x + (baseImg.getGlobalBounds().width / 2), baseImg.getPosition().y + (baseImg.getGlobalBounds().height / 2)));
	bigHand.setScale(1, 1);
	bigHand.setRotation(180);
}

void AnClock::setNewTime(const Time & time)
{
	AnTime = time;
}
void AnClock::setNewTime()
{
	AnTime.setRandTime();
}

Time AnClock::getTime()
{
	return AnTime;
}

void AnClock::update(float& deltaTime)
{
	float hour = AnTime.getHours();
	if (hour >= 12)
		hour = hour - 12;
	hour = hour + (AnTime.getMinutes() / 60.f);

	AnTime.update(deltaTime);
	bigHand.setRotation((float)180 + (AnTime.getMinutes()*6));
	smallHand.setRotation((float)180 + (hour*30.f));
}

void AnClock::render(sf::RenderWindow & window)
{
	window.draw(clockNum);
	window.draw(baseImg);
	window.draw(bigHand);
	window.draw(smallHand);
	//window.draw(secondsHand);
}
