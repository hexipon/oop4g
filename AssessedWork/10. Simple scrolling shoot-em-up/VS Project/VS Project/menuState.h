#pragma once
#include"SpriteBatch.h"
#include"d3d.h"
#include"Sprite.h"
class menuState
{
public:
	static menuState& Get() { menuState Instance; return Instance; }
	void update(const float& deltaTime);
	void render(d3d& d3d, DirectX::SpriteBatch* spritebatch);

};

