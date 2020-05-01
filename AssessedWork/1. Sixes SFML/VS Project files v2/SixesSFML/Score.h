#pragma once
/*
	The players score in a dice gambling game
*/
class Score
{
public:
	//set score to 0
	void init();
	//get the current score
	int getAmount() const;
	//update the score
	//value = any integer
	//positive int gets added to the score
	//negative int get subtracted from the score
	void updateAmount(int value);
private:
	int amount_; //the score value
};