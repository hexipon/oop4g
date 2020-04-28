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
	static gameManager* Get() { 
		if (!instance)
		{
			game = new gameManager();
			instance = true;
			return game;
		}
		else
			return game;
	}


	gameManager(gameManager const&) = delete;             
	gameManager(gameManager&&) = delete;                  
	gameManager& operator=(gameManager const&) = delete;  
	gameManager& operator=(gameManager &&) = delete;      

	void Init(MyD3D&);
	void Run(MyD3D&);
	void updateInput(const WPARAM& wparam);
	const void Release(){
		if (gpSpriteBatch)
		{
			delete gpSpriteBatch;
			gpSpriteBatch = nullptr;
		}
		delete font;
		font = nullptr;
		for (unsigned int i = 0; i < anClocks->size(); i++)
		{
			anClocks->at(i)->Release();
			delete anClocks->at(i);
			anClocks->at(i) = nullptr;
		}
		anClocks->clear();
		digClock.Release();
		state = State::Exit;
		
	}
private:
	gameManager();
	~gameManager() {
		instance = false;
	}
	static bool instance;
	static gameManager *game;
	enum State { Playing, Limbo, Exit };
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

