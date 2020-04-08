#pragma once
#include <ctime>
#include <string>	
class RandomNumberGenerator {
public:
	RandomNumberGenerator();
	int getRandomValue(int) const;
private:
	void seed() const;
};