#pragma once
#include<random>
#include<time.h>
class RandomNumberGenerator
{
public:
	void seed() const;
	int getRandomValue(int) const;
};

