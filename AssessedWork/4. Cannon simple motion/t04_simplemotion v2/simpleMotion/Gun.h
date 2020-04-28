#pragma once
#include"GameObj.h"
#include"GDC.h"
class Application;
//cannon spins around and can fire one cannon ball
class Gun : public GameObj
{
public:
	Gun(GameObj& _ball)
		:GameObj(), WaitSecs(0), ball(_ball)
	{}
	void Update();
private:
	const float X_Offset = -50, Y_Offset = -26;
	const float Ball_X_Offset = -10, Ball_Y_Offset = -5;
	GameObj& ball;
	float WaitSecs;	//delay after firing beforeo you can move/fire
};