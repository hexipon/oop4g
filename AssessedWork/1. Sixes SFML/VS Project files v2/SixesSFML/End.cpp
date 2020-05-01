#include"stdafx.h"
#include "End.h"



bool End::checkInput(int code)
{
	return(false);
}

void End::update()
{
	text.setString(string + "'s final score is:" + std::to_string(score) + "\t\t\t\t\t\t\tpress the Escape or Enter Key to Exit");
}

int End::getNextScene()
{
	window.close(); //no more scenes, close application 
	return(0);
}