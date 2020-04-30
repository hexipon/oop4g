#pragma once
#include"RandomNumberGenerator.h"
/*
A dice in a dice gambling game
*/
class Dice
{
public:
	//make the number generated actually random
	void init();
	//get the value of face_ 
	int getFace() const;
	//generate a random dice face value between 1 and 6
	void roll();
private:
	int face_;						//the number on the dice
	RandomNumberGenerator rng_; 	//the private random number generator
};