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
