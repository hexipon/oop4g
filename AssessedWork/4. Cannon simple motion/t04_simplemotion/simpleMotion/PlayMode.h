#pragma once

#include<assert.h>
#include"Wall.h"
#include"Gun.h"
#include"Ball.h"
#include"GD.h"
class Game;
//in this mode the player can spin the cannon, like a game's playable part
//similar structure to the NameMode, imagine more of these objects for each
//significant part of the game, all structured the same way
class PlayMode
{
public:
	PlayMode() : mpGame(nullptr) {}
	void Init(Game*);
	void Update();
	void Render();
private:
	Game *mpGame; //for communication

	sf::Texture mCannonTex;			//cannon and ball
	sf::Texture mWallTex;			//walls
	Wall mWalls[Wall::MAX_WALLS];	//four walls
	Ball ball;		//ball
	Gun* mGun=NULL;		//cannon
};