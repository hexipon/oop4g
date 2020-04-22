#pragma once
#include <string>	
#include <iostream>
#include"Score.h"
class Player {
public:
	std::string getName() const;
	int getScoreAmount() const;
	void readInName();
	int readInNumberOfGoes() const;
	void updateScore(int);
private:
	std::string name_;
	Score score_;
};