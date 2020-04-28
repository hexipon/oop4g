#pragma once
#include<random>
#include"Singleton.h"
#include<vector>
#include"d3d.h"
#include"SpriteBatch.h"
#include"Sprite.h"
#include"WindowUtils.h"
#include"SimpleMath.h"
#include"d3dUtils.h"
#include"Asteroid.h"
#include"WindowUtils.h"
#include"Missile.h"
#include"SpriteFont.h"
#include"Score.h"
class playState : public Singleton<playState>
{
public:
	playState(d3d& _d3d) : Player(_d3d), Thrust(_d3d), _score(_d3d) { 
		InitBackground(_d3d);
		InitPlayer(_d3d);
		InitAsteroids(_d3d);
	}
	void reset(d3d& _d3d) {
		_score.score = 0;
		InitPlayer(_d3d);
		InitAsteroids(_d3d);
	}
	void update(const float& deltaTime, d3d& _d3d);
	void render(d3d& d3d, DirectX::SpriteBatch& spritebatch);
private:
	const int BGND_LAYERS = 3;
	const float SPEED = 250;
	const float PAD_SPEED = 5000;
	std::vector<Asteroid> Asteroids;
	std::vector<Sprite> Bgnd;
	std::vector<Missile> Missiles;
	Sprite Player;
	
	RECTF PlayArea;

	void InitBackground(d3d& _d3d);
	void InitPlayer(d3d& _d3d);
	float Thrusting = 0;
	Sprite Thrust;
	void UpdateThrust(float dTime);

	float SpawnRateSec = 0.5;
	float LastSpawn = 0;	



	Asteroid* SpawnAsteroid();
	void InitAsteroids(d3d& _d3d);
	Score _score;
	float missileTimer=0.0f;

};

