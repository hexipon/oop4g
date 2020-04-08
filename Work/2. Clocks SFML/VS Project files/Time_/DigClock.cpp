#include "DigClock.h"
void DigClock::init(const sf::Font& font)
{
	if (!tex.loadFromFile("digital_clock.png"))
		throw("Error loading digital clock texture!");
	baseImg.setTexture(tex);
	baseImg.setPosition(sf::Vector2f(position.x + baseImg.getGlobalBounds().width / 2, position.y + baseImg.getGlobalBounds().height / 2));
	baseImg.setScale(.5, .5);
	timeT.setFont(font);
	timeT.setPosition(baseImg.getPosition().x + 40, baseImg.getPosition().y + 45);
	timeT.setLetterSpacing(1);
	timeT.setScale(2, 2);
}

void DigClock::update(float& deltaTime)
{
	//conv time to string
	DiTime.update(deltaTime);
	std::ostringstream os;
	const char prev(os.fill('0'));
	os << std::setw(2) << std::to_string(DiTime.getHours()) << ':'
		<< std::setw(2) << std::to_string(DiTime.getMinutes()) << ':'
		<< std::setw(2) << std::to_string(DiTime.getSeconds());
	os.fill(prev);
	timeT.setString(os.str());
}

void DigClock::render(sf::RenderWindow & window)
{
	window.draw(baseImg);
	window.draw(timeT);
}
