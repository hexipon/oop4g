#include "RandomNumberGenerator.h"
RandomNumberGenerator::RandomNumberGenerator() {
	seed();	//reset the random number generator from current system time
}
void RandomNumberGenerator::seed() const {
	srand(static_cast<unsigned int>(time(0)));
}
int RandomNumberGenerator::getRandomValue(int max) const {
	return (rand() % max) + 1; //produce a random number in range [1..max]
}