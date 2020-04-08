#include"stdafx.h"
#include "Game.h"
void Game::init() {
	dice1_.init();
	dice2_.init();
}
int Game::play(const int& goes, std::vector<sf::Text>& lines, const sf::Font& font) {
	Score score;
	score.init();
		sf::Text text;
		text.setFont(font);
		text.setPosition(0, 0);
	for (int i = 0; i < goes; i++)
	{
		dice1_.roll();
		dice2_.roll();

		setTextString(text, "Try no: " + std::to_string(i+1) + std::string(" || Values: ") + std::to_string(dice1_.getFace()) + " & " + std::to_string(dice2_.getFace()), lines);

		if (dice1_.getFace() == dice2_.getFace())
		{
			score.updateAmount(dice1_.getFace());
			if (dice1_.getFace() == 6)
			{
				setTextString(text, "Jackpot!!!", lines);
				score.updateAmount(score.getAmount());
			}
		}
		else
			if ((dice1_.getFace() == 6) || (dice2_.getFace() == 6))
				score.updateAmount(1);
		setTextString(text, "The Current score is: " + std::to_string(score.getAmount()), lines);
	}
	return score.getAmount();
}

void Game::setTextString(sf::Text text, const sf::String string, std::vector<sf::Text>& lines)
{
	text.setString(string);
	lines.push_back(text);
}

Game::Game()
{
	init();
}
