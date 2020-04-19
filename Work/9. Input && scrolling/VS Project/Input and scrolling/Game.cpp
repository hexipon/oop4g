#include "Game.h"

using namespace std;
using namespace DirectX;
using namespace DirectX::SimpleMath;

MouseKeys Game::sMKIn;
Gamepad Game::sGamepads; 

Game::Game(d3d& d3d)
	: mPMode(d3d), mD3D(d3d), mpSB(nullptr)
{
	sMKIn.Initialise(WinUtil::Get().GetMainWnd(), true, false);
	sGamepads.Initialise();
	mpSB = new SpriteBatch(&mD3D.GetDeviceCtx());
}


//release memory and resources
void Game::Release()
{
	delete mpSB;
	mpSB = nullptr;
}

void Game::Update(float dTime)
{
	sGamepads.Update();
	switch (state)
	{
	case State::PLAY:
		mPMode.Update(dTime);
	}
}

void Game::Render(float dTime)
{
	mD3D.BeginRender(Colours::Black);


	CommonStates dxstate(&mD3D.GetDevice());
	mpSB->Begin(SpriteSortMode_Deferred, dxstate.NonPremultiplied(), &mD3D.GetWrapSampler());

	switch (state)
	{
	case State::PLAY:
		mPMode.Render(dTime, *mpSB);
	}

	mpSB->End();


	mD3D.EndRender();
	sMKIn.PostProcess();
}