#include "NameMode.h"
#include"Game.h"
//******************************************************************
//a mini game frontend
void NameMode::TextEntered(char key)
{
	std::string& nm = Game.GetData().playerName;
	if (key == GDC::ENTER_KEY && nm.length() > 0)
	{
		Game.SetState(Game::StateMachine::PLAY);
	}
	else
	{
		if (isalpha(key))
			nm += key;
	}
}

void NameMode::Render()
{
	std::string mssg = "Type your name (press enter when complete): ";
	mssg += Game.GetData().playerName;
	sf::Text txt(mssg, Game.GetData().font, textSize);
	txt.setPosition(textPosition);
	Game.GetData().pWindow->draw(txt);
}