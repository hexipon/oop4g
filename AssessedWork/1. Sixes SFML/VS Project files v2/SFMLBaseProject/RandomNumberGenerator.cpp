#include"stdafx.h"
#include "RandomNumberGenerator.h"

void RandomNumberGenerator::seed() const
{
	srand(static_cast<unsigned>(time(0)));
}

int RandomNumberGenerator::getRandomValue(int max) const
{
	return (rand() % max);
}