#pragma once
#include"State.h"
/*
get the player to input the number of dice rolls they want
*/
class NumberInput : public State
{
private:
	//ensure the input is between 0-99
	bool checkInput(int unicode);
public:
	NumberInput(sf::RenderWindow& window, sf::Text& text, sf::String& string) :
		State(window, text, string)
	{}
	//update the text string with the number the player is inputting
	void update();
	//return 2 to roll the dice
	int getNextScene();
};

