#include "DiceGame.h"


void DiceGame::init() {
	dice1_.init();
	dice2_.init();
}
int DiceGame::play(const int& goes, std::vector<std::string>& lines) {
	Score score;
	score.init();
	std::string baseString;
	for (int i = 0; i < goes; i++)
	{
		dice1_.roll();
		dice2_.roll();

		setTextString(baseString, "Try no: " + std::to_string(i + 1) + std::string(" || Values: ") + std::to_string(dice1_.getFace()) + " & " + std::to_string(dice2_.getFace()), lines);

		if (dice1_.getFace() == dice2_.getFace())
		{
			score.updateAmount(dice1_.getFace());
			if (dice1_.getFace() == 6)
			{
				setTextString(baseString, "Jackpot!!!", lines);
				score.updateAmount(score.getAmount());
			}
		}
		else
			if ((dice1_.getFace() == 6) || (dice2_.getFace() == 6))
				score.updateAmount(1);
		setTextString(baseString, "The Current score is: " + std::to_string(score.getAmount()), lines);
	}
	return score.getAmount();
}

void DiceGame::setTextString(std::string text, const std::string string, std::vector<std::string>& lines)
{
	text=(string);
	lines.push_back(text);
}

DiceGame::DiceGame()
{
	init();
}
