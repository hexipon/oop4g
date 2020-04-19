#pragma once
#include"stdafx.h"
#include"Dice.h"
#include"Score.h"
class Game {
private:
	Dice dice1_;
	Dice dice2_;
	void init();
	void setTextString(sf::Text text, const sf::String string, std::vector<sf::Text>& lines);
public:
	Game();
	int play(const int & goes, std::vector<sf::Text>& lines, const sf::Font& font);
};