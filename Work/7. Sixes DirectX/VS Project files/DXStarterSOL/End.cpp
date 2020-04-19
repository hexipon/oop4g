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