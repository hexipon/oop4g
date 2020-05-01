#pragma once
#include <string>
#include <iomanip>
#include"SpriteFont.h"
#include"Singleton.h"
#include"d3d.h"
#include"SpriteBatch.h"
#include"SimpleMath.h"
class Score : public Singleton<Score>
{
public:
	Score(d3d& _d3d) : font(&_d3d.GetDevice(), L"assets/retro.spritefont") {
	}
	int score = 0;
	DirectX::SpriteFont font;

	void Render(DirectX::SpriteBatch & spritebatch) {
		std::stringstream _score;
		_score << std::setfill('0') << std::setw(3) << score;
		font.DrawString(&spritebatch, _score.str().c_str(), DirectX::SimpleMath::Vector2(20, 20), Colours::White,0, DirectX::SimpleMath::Vector2(0, 0), DirectX::SimpleMath::Vector2(2, 2));
	}
};

