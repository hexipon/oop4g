#pragma once
#include"Singleton.h"
#include"d3d.h"
#include"SpriteBatch.h"
#include"MouseKeys.h"
#include"Gamepad.h"
#include<stack>
#include"WindowUtils.h"
#include"Menu.h"
#include"CommonStates.h"
#include"Instructions.h"
#include"Settings.h"
#include"Playing.h"
#include"Pause.h"
#include"End.h"
class Manager : public Singleton<Manager>
{
public:

	static MouseKeys mouseAndKeyInput;
	static Gamepad GamepadInput;
	const enum gameStates { GameMenu, GameInstructions, GameSettings, PlayingGame, PausedGame, EndGame };
	Manager(d3d& _d3d) : d3d(_d3d), spriteBatch(DirectX::SpriteBatch(&d3d.GetDeviceCtx())) {
		mouseAndKeyInput.Initialise(WindowUtils::Get().GetMainWnd(), true, false);
		GamepadInput.Initialise();
		_d3d.GetCache().LoadTexture(&_d3d.GetDevice(), "backgrounds/star1alpha.dds");
		_d3d.GetCache().LoadTexture(&_d3d.GetDevice(), "backgrounds/star2alpha.dds");
		_d3d.GetCache().LoadTexture(&_d3d.GetDevice(), "backgrounds/staticBackground.dds");
		_d3d.GetCache().LoadTexture(&_d3d.GetDevice(), "backgrounds/PauseBackground.dds");
		_d3d.GetCache().LoadTexture(&_d3d.GetDevice(), "Player/PGreen.dds");
		_d3d.GetCache().LoadTexture(&_d3d.GetDevice(), "Player/PBlue.dds");
		_d3d.GetCache().LoadTexture(&_d3d.GetDevice(), "Player/POrange.dds");
		_d3d.GetCache().LoadTexture(&_d3d.GetDevice(), "Player/PPurple.dds");
		_d3d.GetCache().LoadTexture(&_d3d.GetDevice(), "Player/PRed.dds");
		_d3d.GetCache().LoadTexture(&_d3d.GetDevice(), "Player/PYellow.dds");
		_d3d.GetCache().LoadTexture(&_d3d.GetDevice(), "PlayerShield.dds");
		_d3d.GetCache().LoadTexture(&_d3d.GetDevice(), "Boss/BGREEN.dds");
		_d3d.GetCache().LoadTexture(&_d3d.GetDevice(), "Boss/BBLUE.dds");
		_d3d.GetCache().LoadTexture(&_d3d.GetDevice(), "Boss/BORANGE.dds");
		_d3d.GetCache().LoadTexture(&_d3d.GetDevice(), "Boss/BPURPLE.dds");
		_d3d.GetCache().LoadTexture(&_d3d.GetDevice(), "Boss/BRED.dds");
		_d3d.GetCache().LoadTexture(&_d3d.GetDevice(), "Boss/BYELLOW.dds");
		_d3d.GetCache().LoadTexture(&_d3d.GetDevice(), "TopBar.dds");
		const RECTF playerBulletAnim[4]{
			{ 211,  8, 222, 18},
			{ 228, 8, 243, 18 },
			{ 249, 8, 267,18 },
			{ 275, 8, 295, 18 }
		};
		std::vector<RECTF> frames(playerBulletAnim, playerBulletAnim + sizeof(playerBulletAnim) / sizeof(playerBulletAnim[0]));
		_d3d.GetCache().LoadTexture(&_d3d.GetDevice(), "Bullets.dds", "PlayerBullets", true, &frames);
		const RECTF enemyBulletAnim[4]{
			{ 138,  5, 151, 22},
			{ 155,	5, 170, 22 },
			{ 174,	5, 191,	22 },
			{ 155,	5, 170, 22 }
		};
		std::vector<RECTF> frames2(enemyBulletAnim, enemyBulletAnim + sizeof(enemyBulletAnim) / sizeof(enemyBulletAnim[0]));
		_d3d.GetCache().LoadTexture(&_d3d.GetDevice(), "Bullets.dds", "EnemyBullets", true, &frames2);
		changeState(GameMenu);
	}
	~Manager() {
		for (auto& state : states)
		{
			delete state;
			state = nullptr;
		}
		states.clear();
	}
	const void changeState(const gameStates& _state);
	const void startGameLoop();
	const void resChange() {
		if (currentState == gameStates::GameSettings)
			states.front()->sizeSetup();
	}
private:
	d3d& d3d;
	DirectX::SpriteBatch spriteBatch;
	gameStates currentState;
	std::vector<State*> states;
	float deltaTime = 0;
	bool canUpdateRender=true;

	const void update();
	const void render();
};

