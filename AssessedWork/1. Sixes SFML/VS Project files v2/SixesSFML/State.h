#pragma once
#include"stdafx.h"
/*
	base class for the states of the gambling dice game
*/
class State
{
protected:
	sf::Window& window;
	sf::Text& text;
	sf::String& string;
	virtual bool checkInput(int code) = 0;
	State(sf::RenderWindow& window, sf::Text& text, sf::String& string):
		window(window),
		text(text),
		string(string)
	{}
public:
	virtual void update()=0;
	//add the character typed to the string that will 
	//be displayed using text
	void updateInput(sf::Event& event);
	//allow the play to use the backspace key
	//to delete the character on the end of the string
	void backspace();
	virtual int getNextScene()=0;
};