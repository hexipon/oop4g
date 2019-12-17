#include <windows.h>
#include <string>
#include <cassert>
#include <d3d11.h>
#include <iomanip>
#include<stack>
#include<vector>
#include<string>
#include "WindowUtils.h"
#include "D3DUtil.h"
#include "D3D.h"
#include "SimpleMath.h"
#include "SpriteFont.h"
#include"State.h"
#include"Game.h"
#include"DiceGame.h"
#include"nameInput.h"
#include"End.h"
#include "NumberInput.h"


bool NumberInput::checkInput(int code)
{
	return(code >= (char)'0') && (code <= (char)'9') && (string.length() < 2);
}

void NumberInput::update()
{
	baseString=("How many goes would you like? " + string);
}

int NumberInput::getNextScene()
{
	return(2);
}