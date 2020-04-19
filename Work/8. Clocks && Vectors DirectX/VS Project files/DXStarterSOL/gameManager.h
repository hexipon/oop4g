#pragma once
#include<vector>
#include"Time.h"
#include"DigClock.h"
#include"AnClock.h"
#include"D3D.h"
#include"SimpleMath.h"
#include"SpriteBatch.h"
#include"SpriteFont.h"
#include"CommonStates.h"
class gameManager
{
public:
	static gameManager& Instance() { static gameManager game; return game; }
	void Init(MyD3D&);
	void updateInput(const WPARAM& wparam);
private:
	gameManager();
	~gameManager() {
		delete gpSpriteBatch;
		gpSpriteBatch = nullptr;
		delete font;
		font = nullptr;
		for (int i = 0; i < anClocks->size(); i++)
		{
			delete anClocks->at(i);
			anClocks->at(i) = nullptr;
		}
		anClocks->clear();
	}
	enum State { Playing, Limbo };
	State state = State::Playing;
	std::vector<AnClock*> anClocks[3];
	DirectX::SimpleMath::Vector2 topTextPos{ 0, 0 };
	DirectX::SimpleMath::Vector2 bottomTextPos{ 0, 500 };
	DigClock digClock;
	DirectX::SpriteBatch *gpSpriteBatch = nullptr;
	DirectX::SpriteFont *font;
	bool correctAnswer = false;
	bool canUpdateRender;
	float deltaTime=0;

	Time correctTime;

	void checkIfCorrect(const int code);
	void update();
	void render(MyD3D& d3d);

	void setClocks();
};

