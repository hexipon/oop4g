#pragma once
#include"Sprite.h"
#include"d3d.h"
#include"SpriteBatch.h"
#include"SimpleMath.h"
#include"gameConstants.h"
#include"Score.h"
class Asteroid
{
public:
	Asteroid(d3d& _d3d)
		:spr(_d3d)
	{}
	Sprite spr;
	int health = 10;
	bool active = false;
	void Init(d3d& _d3d);
	void Render(DirectX::SpriteBatch& batch);
	void Update(float dTime);
	bool CheckCollision(Sprite & sprite);
};

