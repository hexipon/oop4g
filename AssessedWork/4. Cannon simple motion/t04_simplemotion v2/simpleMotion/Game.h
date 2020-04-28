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

	Game() : NMode(*this), PMode(*this), State(StateMachine::WAITING_INIT) {
	}
	//setup
	void Initialise(sf::RenderWindow&);
	//logic
	void Update();
	//display
	void Render();
	//input from windows
	void TextEntered(char);

	//accessors
	StateMachine& GetState() { return State; }
	void SetState(StateMachine nState) { State = nState; }

	GD& GetData() { return GD; }
private:
	GD GD;				//shared game data, be careful here we are breaking rules of encapsulation
	StateMachine State;//contols what's going on in the 
	PlayMode PMode;	//object used for playing the game (like a mini game)
	NameMode NMode;	//object used for getting the player's name (like a mini frontend)
};

