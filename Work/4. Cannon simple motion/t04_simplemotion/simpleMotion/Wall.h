#pragma once
#include"GameObj.h"
#include"Ball.h"
//cannon balls bounce off walls
class Wall : public GameObj
{
public:
	static const int MAX_WALLS = 4;				//a wall on each side of the screen
	enum WallType { LEFT, RIGHT, TOP, BOTTOM };	//identify where each wall is

	Wall()
		:GameObj(), mType(LEFT)
	{}
	void Init(WallType wtype, Ball& _ball) {
		mType = wtype;
		ball = &_ball;
	}
	void Update();
private:
	Ball* ball;
	WallType mType; //where does this instance fit on screen
};