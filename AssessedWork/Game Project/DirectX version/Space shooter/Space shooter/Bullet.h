#pragma once
#include"d3d.h"
#include"Sprite.h"
#include"gameData.h"

class Bullet
{
private:
	const enum colourType { GREEN, BLUE, PURPLE, RED, ORANGE, YELLOW };
	colourType colour = colourType::GREEN;
	Sprite spr;
	DirectX::SpriteBatch& _spritebatch;
	d3d& _d3d;
	float& deltaTime;
	const float MISSILE_SPEED = 500.0f;
	float aditionalSpeed=0.f;
	const float direction;
public:
	Bullet(d3d& d3d_, DirectX::SpriteBatch& _spritebatch, float& _deltaTime, const std::string BulletName, const float _direction )
		: _d3d(d3d_), spr(d3d_), _spritebatch(_spritebatch), deltaTime(_deltaTime), direction(_direction)
	{
		spr.SetTex(*_d3d.GetCache().Get(BulletName).pTex);
		spr.SetScale(DirectX::SimpleMath::Vector2(gameData::Get().WindowSize.x / gameData::Get().MaxWindowSize.x, gameData::Get().WindowSize.y / gameData::Get().MaxWindowSize.y));
		active = true;
	}
	const void Init(const DirectX::SimpleMath::Vector2& pos, const int& _colourtype, const float& velocityX) {
		colour = colourType(_colourtype);
		aditionalSpeed = velocityX;
		spr.GetAnim().Init(0, 3, 3, true);
		spr.GetAnim().Play(true);
		spr.SetScale(DirectX::SimpleMath::Vector2(gameData::Get().WindowSize.x / gameData::Get().MaxWindowSize.x, gameData::Get().WindowSize.y / gameData::Get().MaxWindowSize.y));
		spr.SetPosition(DirectX::SimpleMath::Vector2(pos.x - (spr.GetScreenSize().x / 2), pos.y - (spr.GetScreenSize().y / 2)));
		switch (colour)
		{
		case Bullet::GREEN:
			spr.setColour(Colours::Green);
			break;
		case Bullet::BLUE:
			spr.setColour(Colours::Cyan);
			break;
		case Bullet::PURPLE:
			spr.setColour(Colours::Purple);
			break;
		case Bullet::RED:
			spr.setColour(Colours::Red);
			break;
		case Bullet::ORANGE:
			spr.setColour(Colours::Orange);
			break;
		case Bullet::YELLOW:
			spr.setColour(Colours::Yellow);
			break;
		default:
			break;
		}
	}
	bool active = false;
	void Render();
	void Update();
	const bool CheckCollision(Sprite & sprite);
	const Sprite& getSprite() {
		return spr;
	}
	const void hasCollided() {
		active = false;
	}
	const void setAnimTrue() {
		spr.GetAnim().Play(true);
	}
	const int getColour() {
		return colour;
	}
	Bullet& operator=(const Bullet& rhs) {
		colour = rhs.colour;
		spr = rhs.spr;
		deltaTime = rhs.deltaTime;
		aditionalSpeed = rhs.aditionalSpeed;
		active = rhs.active;
		return *this;
	}
};

