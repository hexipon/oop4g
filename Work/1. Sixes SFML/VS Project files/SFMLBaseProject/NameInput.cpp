#include"stdafx.h"
#include "NameInput.h"

bool NameInput::checkInput(int code)
{
	return((code >= (char)'A') && (code <= (char)'Z') || (code >= (char)'a') && (code <= (char)'z')) &&(string.getSize()<10);
}

void NameInput::update()
{
	text.setString("What's your name? " + string);
}

int NameInput::getNextScene()
{
	return(1);
}