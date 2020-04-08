#include "Player.h"

int Player::getScoreAmount() const {
	return score_.getAmount();
}
std::string Player::getName() const {
	return name_;
}
void Player::updateScore(int value) {
	score_.updateAmount(value);
}
int Player::readInNumberOfGoes() const {
	//ask the user for the number of dice throws
	int num;
	std::cout << "\nHow many goes do you want? ";
	std::cin >> num;
	return(num);
}
void Player::readInName() {
	//ask the user for his/her name
	std::cout << "\nEnter your name? ";
	std::cin >> name_;
}