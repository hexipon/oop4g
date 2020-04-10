#include "NameMode.h"
#include"Game.h"
//******************************************************************
//a mini game frontend
void NameMode::TextEntered(char key)
{
	assert(mpGame);
	std::string& nm = mpGame->GetData().playerName;
	if (key == GDC::ENTER_KEY && nm.length() > 0)
	{
		mpGame->SetState(Game::StateMachine::PLAY);
	}
	else
	{
		if (isalpha(key))
			nm += key;
	}
}

void NameMode::Render()
{
	assert(mpGame);
	std::string mssg = "Type your name (press enter when complete): ";
	mssg += mpGame->GetData().playerName;
	sf::Text txt(mssg, mpGame->GetData().font, 30);
	txt.setPosition(100, 100);
	mpGame->GetData().pWindow->draw(txt);
}

void NameMode::Init(Game *pG)
{
	assert(!mpGame);
	mpGame = pG;
}