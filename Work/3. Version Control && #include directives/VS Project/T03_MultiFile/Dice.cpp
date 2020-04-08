#include "Dice.h"
Dice::Dice() : face_(0)
{}
int Dice::getFace() const {
	return face_;	//get value of dice face
}
void Dice::roll() {
	static RandomNumberGenerator srng; 	//static local RandomNumberGenerator
	face_ = srng.getRandomValue(6); 	//roll dice
}