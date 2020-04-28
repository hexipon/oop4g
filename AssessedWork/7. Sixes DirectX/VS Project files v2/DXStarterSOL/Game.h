#pragma once
#include<stack>
#include<vector>
#include "WindowUtils.h"
#include "D3D.h"
#include "SimpleMath.h"
#include "SpriteFont.h"
#include"nameInput.h"
#include"NumberInput.h"
#include"DiceGame.h"
#include"End.h"
class Game
{
private:
	Game() {}
	float gameTime=0;
	float deltaTime=0; 
	int gCycle = 0;
	float gResTimer = 0;
	DirectX::SimpleMath::Vector4 gColours[8];
	DirectX::SpriteBatch *gpSpriteBatch = nullptr;
	bool canUpdateRender;

	void numScene(MyD3D& d3d);
	void rollDice(MyD3D& d3d);

	std::vector<std::string> lines;
	std::string playerName;
	std::string numInput;
	int score;
public:
	static Game& Instance() { static Game game; return game; }
	void init(MyD3D& d3d);
	void UpdateAndRender(MyD3D& d3d); //update and render
	std::stack<State*> states;
	void nextScene(MyD3D& d3d, const int &);
	void ReleaseGame();


};

