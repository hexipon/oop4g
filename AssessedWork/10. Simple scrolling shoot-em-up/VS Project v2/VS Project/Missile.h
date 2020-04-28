#pragma once
#include<vector>
#include"d3d.h"
#include"SpriteBatch.h"
#include"Sprite.h"
#include"WindowUtils.h"
class Missile
{
public:
	Missile(d3d& _d3d)
		:spr(_d3d)
	{}
	Sprite spr;
	bool active = false;

	void Init(d3d& _d3d);
	void Render(DirectX::SpriteBatch& batch);
	void Update(float dTime);
	bool CheckCollision(Sprite & sprite);
	const float MISSILE_SPEED = 300;
};

