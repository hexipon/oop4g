#pragma once
#include"D3D.h"
#include"Time.h"
#include"SpriteFont.h"
#include"SpriteBatch.h"
#include"Sprite.h"
#include"SimpleMath.h"
class DigClock
{
private:
	DirectX::SpriteFont *font;
	DirectX::SimpleMath::Vector2 digTextPos{ 0, 0 };
	Time& DiTime;
	std::string timeT;
	const DirectX::SimpleMath::Vector2 position{ 350, 50 };
public:
	DigClock(Time& DiTime) : DiTime(DiTime) {};
	const void Release() {
		delete font;
		font = nullptr;
	}
	void init(MyD3D&);
	void update(float& deltaTime);
	void render(MyD3D& d3d, DirectX::SpriteBatch& spritebatch);
};

