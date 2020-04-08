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
#include"nameInput.h"
//#include"NumberInput.h"

bool NameInput::checkInput(int code)
{
	return((code >= (char)'A') && (code <= (char)'Z') || (code >= (char)'a') && (code <= (char)'z')) && (string.length() < 10);
}

void NameInput::update()
{
	baseString=("What's your name? " + string);
}

int NameInput::getNextScene()
{
	return(1);
}
