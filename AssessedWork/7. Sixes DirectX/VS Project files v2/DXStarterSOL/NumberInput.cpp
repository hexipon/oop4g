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