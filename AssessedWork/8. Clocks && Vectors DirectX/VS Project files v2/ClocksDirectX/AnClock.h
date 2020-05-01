#pragma once

#include"Time.h"
#include<d3d11.h>
#include"SimpleMath.h"
#include"SpriteFont.h"
#include"D3D.h"
#include"Sprite.h"
class AnClock
{
private:
	DirectX::SpriteFont *font;
	std::string clockNum;
	Time AnTime;
	const DirectX::SimpleMath::Vector2 position;
	float bigHandRotation;
	float smallHandRotation;

public:
	AnClock(const int i, const DirectX::SimpleMath::Vector2 pos, MyD3D& d3d);
	const void Release() {
		delete font;
		font = nullptr;
	}
	void setNewTime(const Time&);
	void setNewTime();
	void update(float& deltaTime);
	void render(MyD3D&, DirectX::SpriteBatch& spritebatch);
	Time getTime();
};

