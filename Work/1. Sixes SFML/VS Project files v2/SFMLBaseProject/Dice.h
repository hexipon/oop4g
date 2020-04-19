#pragma once
//Include classes 
#include"RandomNumberGenerator.h"
class Dice
{
public:
	void init();
	int getFace() const;
	void roll();
private:
	int face_;		//the number on the dice
	RandomNumberGenerator rng_; 	//the private random number generator
};