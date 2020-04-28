#pragma once
#include"GameObj.h"
//cannon balls bounce off walls
class Wall : public GameObj
{
public:
	static const int MAX_WALLS = 4;				//a wall on each side of the screen
	enum WallType { LEFT, RIGHT, TOP, BOTTOM };	//identify where each wall is

	Wall(GameObj& _ball)
		:GameObj(), Type(LEFT), ball(_ball)
	{}
	void Init(WallType wtype) {
		Type = wtype;
	}
	void Update();
private:
	GameObj& ball;
	WallType Type; //where does this instance fit on screen
};