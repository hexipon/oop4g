#pragma once
/*
Mini game example demonstrates static binding - compile time inheritance and
introduces some simple physics to get things moving. For students to modify
*/
#include"PlayMode.h"
#include"NameMode.h"



//manage the game's different behaviours
class Game
{
public:
	//control what the game is doing 
	enum class StateMachine {
		WAITING_INIT,	//not in a safe state yet
		GET_NAME,		//what's your name?
		PLAY			//let's play!!
	};

	Game();
	//setup
	void Initialise(sf::RenderWindow&);
	//logic
	void Update();
	//display
	void Render();
	//input from windows
	void TextEntered(char);

	//accessors
	StateMachine& GetState() { return mState; }
	void SetState(StateMachine nState) { mState = nState; }

	GD& GetData() { return mGD; }
private:
	GD mGD;				//shared game data, be careful here we are breaking rules of encapsulation
	StateMachine mState;//contols what's going on in the 
	PlayMode mPMode;	//object used for playing the game (like a mini game)
	NameMode mNMode;	//object used for getting the player's name (like a mini frontend)
};

