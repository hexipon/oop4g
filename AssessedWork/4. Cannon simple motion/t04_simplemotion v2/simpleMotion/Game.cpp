#include "Game.h"

/******************************************************************
game implementation code
Note that we can't give mPMode and mNMode constructors, for example: PlayMode(Game&)
which seems obvious and elegant, because the Game object itself wouldn't have finished
constructing, so if in one of those mode objects, it started using the Game& reference,
that would be bad as the Game object might not be completely ready (hence Initialise(Game*)
functions instead). We will learn how to get around that using dynamic allocation later.
*/

void Game::Initialise(sf::RenderWindow& window)
{
	assert(State == StateMachine::WAITING_INIT);
	GD.pWindow = &window;
	//load the font
	if (!GD.font.loadFromFile("data/fonts/comic.ttf"))
		assert(false);

	//setup
	PMode.Init();
	State = StateMachine::GET_NAME;
}

void Game::Update()
{
	switch (State)
	{
	case StateMachine::GET_NAME:
		NMode.Update();
		break;
	case StateMachine::PLAY:
		PMode.Update();
		break;
	}
}

void Game::Render()
{
	switch (State)
	{
	case StateMachine::GET_NAME:
		NMode.Render();
		break;
	case StateMachine::PLAY:
		PMode.Render();
		break;
	}

}

void Game::TextEntered(char key)
{
	//escape overrides everything else, just quit
	switch (key)
	{
	case GDC::ESCAPE_KEY:
		GD.pWindow->close();
		break;
	}

	//pass input messages to different mode objects
	switch (State)
	{
	case StateMachine::GET_NAME:
		NMode.TextEntered(key);
		break;
	case StateMachine::PLAY:
		break;
	default:
		assert(false);
	}
}


















