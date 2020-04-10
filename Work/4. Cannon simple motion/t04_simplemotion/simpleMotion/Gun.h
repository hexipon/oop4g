#pragma once
#include"GameObj.h"
#include"GDC.h"
#include"Ball.h"
class Application;
//cannon spins around and can fire one cannon ball
class Gun : public GameObj
{
public:
	Gun(Ball& _ball)
		:GameObj(), mWaitSecs(0), ball(_ball)
	{}
	void Update();
private:
	Ball& ball;
	float mWaitSecs;	//delay after firing beforeo you can move/fire
};