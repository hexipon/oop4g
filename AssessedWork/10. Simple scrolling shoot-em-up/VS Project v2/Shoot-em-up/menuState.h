#pragma once
#include"SpriteBatch.h"
#include"d3d.h"
#include"Sprite.h"
#include"Singleton.h"
class menuState :public Singleton<menuState>
{
public:
	void update(const float& deltaTime);
	void render(d3d& d3d, DirectX::SpriteBatch* spritebatch);

};

