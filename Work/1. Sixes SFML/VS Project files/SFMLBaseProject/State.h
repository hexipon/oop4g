#pragma once
#include"stdafx.h"
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
	void updateInput(sf::Event& event);
	void backspace();
	virtual int getNextScene()=0;
	//virtual void render() = 0;
};