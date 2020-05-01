#pragma once
#include"stdafx.h"
#include"Dice.h"
#include"Score.h"
/*
A dice gambling game
*/
class Game {
private:
	Dice dice1_;	//hold the data of dice one
	Dice dice2_;	//hold the data of dice two
	//inititate both the dice
	void init();
	//add new line of text 
	//text - the text you you want to add the string to 
	//string - what you want the text to say
	//lines - the list of text that is rendered 
	void setTextString(sf::Text text, const sf::String string, std::vector<sf::Text>& lines);
public:
	//inititiate the game
	Game();
	//goes - any integer value, the number of rolls the player wants to have
	//lines - the list of text that is rendered 
	//font - the font which the text will use 
	int play(const int & goes, std::vector<sf::Text>& lines, const sf::Font& font);
};