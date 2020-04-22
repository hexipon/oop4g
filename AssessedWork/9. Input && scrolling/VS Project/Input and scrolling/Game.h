#pragma once
#include"MouseKeys.h"
#include"Gamepad.h"
#include"d3d.h"
#include"SpriteBatch.h"
#include"PlayState.h"
#include "CommonStates.h"
class Game
{
public:
	enum class State { PLAY };
	static MouseKeys mouseAndKeyInput;
	static Gamepad GamepadInput;
	State state = State::PLAY;
	Game(d3d& d3d);


	void Release();
	void Update(float dTime);
	void Render(float dTime);
private:
	d3d& _d3d;

	DirectX::SpriteBatch *spriteBatch = nullptr;
	PlayState playState;
};