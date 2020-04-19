#include"stdafx.h"
#include "RandomNumberGenerator.h"
//ensure random number is actually random
void RandomNumberGenerator::seed() const
{
	srand(static_cast<unsigned>(time(0)));
}
//produce a random number in range [1..max]
int RandomNumberGenerator::getRandomValue(int max) const
{
	return (rand() % max);
}