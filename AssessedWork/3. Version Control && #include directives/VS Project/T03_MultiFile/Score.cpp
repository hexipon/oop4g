#include "Score.h"
Score::Score()
	: amount_(0)
{}
int Score::getAmount() const {
	return amount_;
}
void Score::updateAmount(int value) {
	//increment when value>0, decrement otherwise
	amount_ += value;
}