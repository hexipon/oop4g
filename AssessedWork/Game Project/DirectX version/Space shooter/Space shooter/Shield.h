#pragma once
#include"d3d.h"
#include"SpriteBatch.h"
#include"Sprite.h"
#include"gameData.h"
class Shield
{
private:
	const enum colourType { GREEN, BLUE, PURPLE, RED, ORANGE, YELLOW };
	colourType colour = colourType::GREEN;
	float timer=0;
	bool active = false;
	d3d& _d3d;
	DirectX::SpriteBatch& _spritebatch;
	float& deltaTime;
	Sprite spr;
public:
	Shield(d3d& d3d_, DirectX::SpriteBatch& spritebatch_, float& deltaTime_) :
		_d3d(d3d_), _spritebatch(spritebatch_), deltaTime(deltaTime_), 
		spr(_d3d) {
		spr.SetTex(*_d3d.GetCache().Get("PlayerShield").pTex);
		spr.SetScale(DirectX::SimpleMath::Vector2(gameData::Get().WindowSize.x / gameData::Get().MaxWindowSize.x, gameData::Get().WindowSize.y / gameData::Get().MaxWindowSize.y));
		active = true;

	}
	const void activate(const float duration) {
		active = true;
		timer = duration;
	}
	const void changeMode(const int mode) {
		colour = colourType(mode);
		switch (colour)
		{
		case Shield::GREEN:
			spr.setColour(Colours::Red);
			break;
		case Shield::BLUE:
			spr.setColour(Colours::Orange);
			break;
		case Shield::PURPLE:
			spr.setColour(Colours::Yellow);
			break;
		case Shield::RED:
			spr.setColour(Colours::Green);
			break;
		case Shield::ORANGE:
			spr.setColour(Colours::Blue);
			break;
		case Shield::YELLOW:
			spr.setColour(Colours::Purple);
			break;
		}
	}
	const void update(const DirectX::SimpleMath::Vector2& pos) {
		spr.SetPosition(pos);
		timer -= deltaTime;
		if (timer <= 0)
			active = false;
	}
	const void render() {
		spr.Draw(_spritebatch);
	}
	const int getColour() {
		return colour;
	}
	const bool isActive() {
		return active;
	}
	const float getRadius() {
		return spr.GetScreenSize().x / 2;
	}
};

