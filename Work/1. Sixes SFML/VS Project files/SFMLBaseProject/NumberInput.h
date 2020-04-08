#pragma once
#include"State.h"
class NumberInput : public State
{
private:
	bool checkInput(int unicode);
public:
	NumberInput(sf::RenderWindow& window, sf::Text& text, sf::String& string) :
		State(window, text, string)
	{}
	void update();
	int getNextScene();
};

