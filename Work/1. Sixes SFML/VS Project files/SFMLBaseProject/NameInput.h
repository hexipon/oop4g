#pragma once
#include"State.h"
#include"NumberInput.h"
class NameInput : public State
{
private:
	bool checkInput(int unicode);
public:
	NameInput(sf::RenderWindow& window, sf::Text& text, sf::String& string) :
		State(window, text, string)
	{}
	void update();
	int getNextScene();
};

