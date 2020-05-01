#include"stdafx.h"
#include "State.h"



void State::updateInput(sf::Event& event)
{
	if(checkInput(event.key.code))
		string += (event.text.unicode);
}

void State::backspace()
{
	if(string.getSize()>0)
		string.erase(string.getSize() - 1,1);
}