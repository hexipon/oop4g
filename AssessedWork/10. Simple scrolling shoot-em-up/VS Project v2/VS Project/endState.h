#pragma once
#include"SpriteBatch.h"
#include"d3d.h"
#include"Sprite.h"
#include"playState.h"
#include"Score.h"
class endState :public Singleton<endState>
{
public:
	void update(const float& deltaTime, d3d& _d3d);
	void render(d3d& d3d, DirectX::SpriteBatch* spritebatch);

};

