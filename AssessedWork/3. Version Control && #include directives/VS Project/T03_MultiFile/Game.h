#pragma once
#include"Dice.h"
#include"Player.h"
class Game {
public:
	explicit Game(Player* pplayer);
	void displayData() const;
	void run();
private:
	Player* p_player_;
	Dice firstDice_, secondDice_;
	int numberOfGoes_;
	void rollDices();
};