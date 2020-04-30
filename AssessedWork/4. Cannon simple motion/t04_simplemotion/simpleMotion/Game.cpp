#include "Game.h"

/******************************************************************
game implementation code
Note that we can't give mPMode and mNMode constructors, for example: PlayMode(Game&)
which seems obvious and elegant, because the Game object itself wouldn't have finished
constructing, so if in one of those mode objects, it started using the Game& reference,
that would be bad as the Game object might not be completely ready (hence Initialise(Game*)
functions instead). We will learn how to get around that using dynamic allocation later.
*/
Game::Game()
	: mState(StateMachine::WAITING_INIT)
{}

void Game::Initialise(sf::RenderWindow& window)
{
	assert(mState == StateMachine::WAITING_INIT);
	mGD.pWindow = &window;
	//load the font
	if (!mGD.font.loadFromFile("../data/fonts/comic.ttf"))
		assert(false);

	//setup
	mNMode.Init(this);
	mPMode.Init(this);
	mState = StateMachine::GET_NAME;
}

void Game::Update()
{
	switch (mState)
	{
	case StateMachine::GET_NAME:
		mNMode.Update();
		break;
	case StateMachine::PLAY:
		mPMode.Update();
		break;
	}
}

void Game::Render()
{
	switch (mState)
	{
	case StateMachine::GET_NAME:
		mNMode.Render();
		break;
	case StateMachine::PLAY:
		mPMode.Render();
		break;
	}

}

void Game::TextEntered(char key)
{
	//escape overrides everything else, just quit
	switch (key)
	{
	case GDC::ESCAPE_KEY:
		mGD.pWindow->close();
		break;
	}

	//pass input messages to different mode objects
	switch (mState)
	{
	case StateMachine::GET_NAME:
		mNMode.TextEntered(key);
		break;
	case StateMachine::PLAY:
		break;
	default:
		assert(false);
	}
}


















