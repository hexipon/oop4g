#pragma once
#include"State.h"
#include"NumberInput.h"
/*
	get the player to input their name
*/
class NameInput : public State
{
private:
	//check if character input is between a-z and is smaller than 10 
	//to keep the name from being too big
	bool checkInput(int unicode);
public:
	NameInput(sf::RenderWindow& window, sf::Text& text, sf::String& string) :
		State(window, text, string)
	{}
	//update text string with the name the player is typing
	void update();
	//Return 1 to change state to number input
	int getNextScene();
};

