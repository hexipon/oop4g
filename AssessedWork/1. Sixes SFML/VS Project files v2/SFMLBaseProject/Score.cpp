#include"stdafx.h"
#include "Score.h"



void Score::init()
{
	amount_ = 0;
}
int Score::getAmount() const
{
	return amount_;
}
void Score::updateAmount(int value)
{
	amount_ += value;
}