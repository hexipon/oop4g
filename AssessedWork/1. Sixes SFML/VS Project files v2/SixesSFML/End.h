#pragma once
#include"stdafx.h"
#include"State.h"
/*
The last state in the dice gambling game
*/
class End : public State
{
private:
	//refuse input
	//unicode - any unicode integer value obtained from input
	bool checkInput(int unicode);
	const int& score;	//the final score obtained at the end of the game
public:
	//set the score value to the final score obtained
	End(sf::RenderWindow& window, sf::Text& text, sf::String& string, const int& score) :
		State(window, text, string), score(score)
	{}
	//set text string to the players name and final score value 
	//and say how to exit the application
	void update();
	//this is the last scene, so close the window
	int getNextScene();
};

