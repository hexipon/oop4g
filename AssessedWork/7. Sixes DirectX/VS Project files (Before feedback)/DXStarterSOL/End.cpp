#include <windows.h>
#include <string>
#include <cassert>
#include <d3d11.h>
#include <iomanip>
#include<stack>
#include<vector>
#include<string>
#include<random>
#include<time.h>
#include "WindowUtils.h"
#include "D3DUtil.h"
#include "D3D.h"
#include "SimpleMath.h"
#include "SpriteFont.h"
#include"State.h"
#include "End.h"



bool End::checkInput(int code)
{
	//refuse input
	return(false);
}

void End::update()
{
	baseString=(string + "'s final score is:" + std::to_string(score) + "                    press the Escape to Exit");
}

int End::getNextScene()
{
	return(3);
}