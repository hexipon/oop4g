#pragma once
/*
	produce a random number for the dice
*/
class RandomNumberGenerator
{
public:
	//make sure the number is actually random
	void seed() const;
	//return a number between 0 and max
	//max - the maximun number the generated number should be
	//for a dice, this is 6
	int getRandomValue(int max) const;
};

