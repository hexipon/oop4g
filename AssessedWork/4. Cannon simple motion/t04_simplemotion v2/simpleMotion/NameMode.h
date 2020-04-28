#pragma once
#include<assert.h>
#include <string>
#include"GDC.h"
#include"Vec2f.h"
//#include"Game.h"
class Game;
//in this mode we want the player's name, like a game's frontend menu screens
class NameMode
{
public:
	NameMode(Game& _game) :Game(_game) {}

	//handle any logic
	void Update() {};
	//display
	void Render();
	//process windows text messages
	void TextEntered(char);
private:
	const Vec2f textPosition{ 100,100 };
	const int textSize{ 30 };
	Game& Game;	//the only way to communicate with the rest of the game
};