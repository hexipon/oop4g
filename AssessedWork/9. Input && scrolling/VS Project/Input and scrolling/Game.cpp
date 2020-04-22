#include "Game.h"

using namespace std;
using namespace DirectX;
using namespace DirectX::SimpleMath;

MouseKeys Game::mouseAndKeyInput;
Gamepad Game::GamepadInput; 

Game::Game(d3d& _d3d)
	: playState(_d3d), _d3d(_d3d), spriteBatch(nullptr)
{
	mouseAndKeyInput.Initialise(WinUtil::Get().GetMainWnd(), true, false);
	GamepadInput.Initialise();
	spriteBatch = new SpriteBatch(&_d3d.GetDeviceCtx());
}

void Game::Release()
{
	delete spriteBatch;
	spriteBatch = nullptr;
}

void Game::Update(float deltaTime)
{
	GamepadInput.Update();
	switch (state)
	{
	case State::PLAY:
		playState.Update(deltaTime);
	}
}

void Game::Render(float deltaTime)
{
	_d3d.BeginRender(Colours::Black);


	CommonStates dxstate(&_d3d.GetDevice());
	spriteBatch->Begin(SpriteSortMode_Deferred, dxstate.NonPremultiplied(), &_d3d.GetWrapSampler());

	switch (state)
	{
	case State::PLAY:
		playState.Render(deltaTime, *spriteBatch);
	}

	spriteBatch->End();


	_d3d.EndRender();
	mouseAndKeyInput.PostProcess();
}