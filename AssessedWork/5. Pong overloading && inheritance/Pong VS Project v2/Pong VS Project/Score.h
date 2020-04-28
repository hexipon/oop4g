#pragma once
#include"GameObject.h"
class Score : public GameObject
{
public:
	static Score& player1Score() { static Score player1Score; return player1Score; }
	static Score& player2Score() { static Score player2Score; return player2Score; }
	const void Render(sf::RenderWindow& window)override {
		window.draw(score);
	}
	const void SetOrigin(const Vec2f& off)override {
		score.setOrigin(off);
	}
	const Vec2f GetScale()override {
		return(score.getScale());
	}
	const Vec2f GetPos() override {
		return score.getPosition();
	}
	const void SetPos(const Vec2f& pos)override {
		score.setPosition(pos);
	}
	const void SetSize(const float& pos) {
		score.setCharacterSize(pos);
	}
	const void SetColour(const sf::Color col)override {
		score.setFillColor(col);
	}
	const sf::FloatRect getGlobalBounds()override {
		return score.getGlobalBounds();
	}
	const void setFont(const std::string fontLocation)
	{
		if (!font.loadFromFile(fontLocation))
			throw("error loading font");
		score.setFont(font);
	}
	const void resetScore() {
		_score = 0;
		score.setString(std::to_string(_score));
	}
	const int getScore() {
		return _score;
	}
	const void operator ++(int) { _score++; score.setString(std::to_string(_score)); }
private:
	Score() { score.setString(std::to_string(_score)); }
	sf::Text score;
	sf::Font font;
	int _score = 0;
};

