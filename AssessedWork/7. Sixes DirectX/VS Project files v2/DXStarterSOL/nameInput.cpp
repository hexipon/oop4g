#include"nameInput.h"

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
