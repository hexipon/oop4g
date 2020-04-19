#pragma once
#include"MouseKeys.h"
#include"Gamepad.h"
#include"d3d.h"
#include"SpriteBatch.h"
#include"PlayMode.h"
#include "CommonStates.h"
class Game
{
public:
	enum class State { PLAY };
	static MouseKeys sMKIn;
	static Gamepad sGamepads;
	State state = State::PLAY;
	Game(d3d& d3d);


	void Release();
	void Update(float dTime);
	void Render(float dTime);
private:
	d3d& mD3D;
	DirectX::SpriteBatch *mpSB = nullptr;
	//not much of a game, but this is it
	PlayMode mPMode;
};