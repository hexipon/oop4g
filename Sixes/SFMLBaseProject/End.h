#pragma once
#include"stdafx.h"
#include"State.h"
class End : public State
{
private:
	bool checkInput(int unicode);
	const int& score;
public:
	End(sf::RenderWindow& window, sf::Text& text, sf::String& string, const int& score) :
		State(window, text, string), score(score)
	{}
	void update();
	int getNextScene();
};

