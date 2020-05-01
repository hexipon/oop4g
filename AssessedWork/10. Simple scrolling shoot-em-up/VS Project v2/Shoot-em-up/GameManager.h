#pragma once
#include"Singleton.h"
#include"d3d.h"
#include"SpriteBatch.h"
#include "WindowUtils.h"
#include"CommonStates.h"
#include"MouseKeys.h"
#include"Gamepad.h"
#include"menuState.h"
#include"playState.h"
#include"endState.h"
class GameManager : public Singleton<GameManager>
{
public:
	static MouseKeys mouseAndKeyInput;
	static Gamepad GamepadInput;
	const enum gameStates{Menu, Playing, Lost};
	const void Init() { 
		cacheTextures();
		playState _playstate(d3d);
		startGameLoop();
	}
	const void Release() {
		delete spriteBatch; 
		spriteBatch = nullptr;
	}
	const void changeState(const gameStates& state)
	{
		currentState = state;
	}
	GameManager(d3d& _d3d) : d3d(_d3d) {
		spriteBatch = new DirectX::SpriteBatch(&d3d.GetDeviceCtx());
		mouseAndKeyInput.Initialise(WindowUtils::Get().GetMainWnd(), true, false);
		GamepadInput.Initialise();
	}
private:
	gameStates currentState = Menu;
	const void startGameLoop();
	const void cacheTextures();
	void update();
	const void render();
	float deltaTime = 0;
	bool canUpdateRender;
	d3d& d3d;
	DirectX::SpriteBatch *spriteBatch = nullptr;

};

