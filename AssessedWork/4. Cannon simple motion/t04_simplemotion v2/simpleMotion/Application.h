#ifndef APPLICATION_H
#define APPLICATION_H

#include"Game.h"

//******************************************************************
//boilerplate setup and manage your game
class Application
{
public:
	Application();
	//this kicks off everything
	void Run();
	//global way to see how much time passed since the last update
	static float GetElapsedSecs() { return sElapsedSecs.asSeconds(); }
private:
	Game Game;
	sf::RenderWindow Window;		//for rendering};
	static sf::Time sElapsedSecs;	//track how much time each update/render takes for smooth motion
};
#endif

