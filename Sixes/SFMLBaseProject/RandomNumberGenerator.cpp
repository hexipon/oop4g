#include"stdafx.h"
#include "RandomNumberGenerator.h"
void RandomNumberGenerator::seed() const
{
	srand(static_cast<unsigned>(time(0)));
}
int RandomNumberGenerator::getRandomValue(int max) const
//produce a random number in range [1..max]
{
	return (rand() % max) + 1;
}