#include "Game.h"

Game::Game(Player* pplayer)
	: p_player_(pplayer), firstDice_(), secondDice_(), numberOfGoes_(0)
{
	p_player_->readInName();
	numberOfGoes_ = p_player_->readInNumberOfGoes();
}
void Game::displayData() const {
	std::cout << "\nPlayer is: " << p_player_->getName();
	std::cout << "\nScore is: " << p_player_->getScoreAmount() << std::endl;
}
void Game::run() {
	for (int i(1); i <= numberOfGoes_; ++i)
	{
		rollDices();
		const int face1(firstDice_.getFace());
		const int face2(secondDice_.getFace());
		std::cout << "\nIn try no: " << i << " \tdice values are: "
			<< face1 << " and " << face2;
		if ((face1 == face2) && (face1 == 6))
			p_player_->updateScore(p_player_->getScoreAmount());
		else
			if (face1 == face2)
				p_player_->updateScore(face1);
		//check current score
		std::cout << "\tThe current score is: " << p_player_->getScoreAmount();
	}
}
void Game::rollDices() {
	firstDice_.roll();
	secondDice_.roll();
}