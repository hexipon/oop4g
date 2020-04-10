#pragma once
#include<assert.h>
#include <string>
#include"GDC.h"
//#include"Game.h"
class Game;
//in this mode we want the player's name, like a game's frontend menu screens
class NameMode
{
public:
	NameMode() :mpGame(nullptr) {}
	//setup
	void Init(Game*);
	//handle any logic
	void Update() {};
	//display
	void Render();
	//process windows text messages
	void TextEntered(char);
private:
	Game *mpGame;	//the only way to communicate with the rest of the game
};