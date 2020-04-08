#include "Dice.h"



void Dice::init()
{
	rng_.seed();
}
int Dice::getFace() const
{
	return face_;
}
void Dice::roll()
{
	face_ = rng_.getRandomValue(6) + 1;
}