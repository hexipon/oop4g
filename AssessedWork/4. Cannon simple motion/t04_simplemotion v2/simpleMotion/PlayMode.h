#pragma once

#include<assert.h>
#include"Wall.h"
#include"Gun.h"
#include"GD.h"
class Game;
//in this mode the player can spin the cannon, like a game's playable part
//similar structure to the NameMode, imagine more of these objects for each
//significant part of the game, all structured the same way
class PlayMode
{
public:
	PlayMode(Game& _game) : Game(_game), mpGun(nullptr), Walls{Wall(ball), Wall(ball), Wall(ball), Wall(ball)} {
		mpGun = new Gun(ball); 
	}
	~PlayMode() {
		delete mpGun;
		mpGun = nullptr;
	}
	void Init();
	void Update();
	void Render();
private:
	const int textSize{ 20 };
	Game& Game; //for communication

	sf::Texture CannonTex;			//cannon and ball
	sf::Texture WallTex;			//walls
	Wall Walls[Wall::MAX_WALLS];	//four walls
	GameObj ball;		//ball
	Gun* mpGun;		//cannon
};