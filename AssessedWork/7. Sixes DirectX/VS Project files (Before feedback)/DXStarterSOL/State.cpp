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
#include "State.h"



void State::updateInput(char code)
{
	if (checkInput(code))
		string += (code);
}

void State::backspace()
{
	if (string.length() > 0)
		string.erase(string.length() - 1, 1);
}
