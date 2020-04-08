#pragma once
//#define MAX_COLOURS 8 
class Game
{
private:
	float gameTime=0;
	float dt=0; //deltatime
	int gCycle = 0;
	float gResTimer = 0;
	DirectX::SimpleMath::Vector4 gColours[8];
	DirectX::SpriteBatch *gpSpriteBatch = nullptr;
	bool canUpdateRender;

	void ReleaseGame();
	void numScene(MyD3D& d3d);
	void rollDice(MyD3D& d3d);

	std::vector<std::string> lines;
	std::string playerName;
	std::string numInput;
	int score;
public:
	void init(MyD3D& d3d);
	void UR(MyD3D& d3d); //update and render
	std::stack<State*> states;
	void nextScene(MyD3D& d3d, const int &);


};

