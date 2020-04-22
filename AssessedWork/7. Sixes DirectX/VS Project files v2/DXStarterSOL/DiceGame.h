#pragma once
#include<string>
#include"Dice.h"
#include"Score.h"
class DiceGame {
private:
	Dice dice1_;
	Dice dice2_;
	void init();
	void setTextString(std::string, const std::string, std::vector<std::string>&);
public:
	DiceGame();
	int play(const int & goes, std::vector<std::string>& lines);
};