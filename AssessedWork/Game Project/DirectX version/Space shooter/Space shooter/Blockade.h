#pragma once
#include"Ship.h"
class Blockade : public Ship
{
private:
	DirectX::SimpleMath::Vector4& PlayArea;
	const std::string textures[6] = { {"BlockadeGreen"},{"BlockadeBlue"},{"BlockadePurple"},{"BlockadeRed"},{"BlockadeOrange"},{"BlockadeYellow"} };

public:
	Blockade(d3d& d3d_, DirectX::SpriteBatch& spritebatch_, float& deltaTime_,
		DirectX::SimpleMath::Vector4& _PlayArea, const int type) :
		Ship(d3d_, spritebatch_, deltaTime_), PlayArea(_PlayArea)
	{
		colour = Ship::colourType(type);
		ship.SetTex(*_d3d.GetCache().Get(textures[type]).pTex);
		ship.SetScale(DirectX::SimpleMath::Vector2(gameData::Get().WindowSize.x / gameData::Get().MaxWindowSize.x, gameData::Get().WindowSize.y / gameData::Get().MaxWindowSize.y));
		speed = 15.f;
		health = 20.f;

	}
	const void init() override {

	}
	const void render() override;
	const void update() override;
	const void hasCollided(const int _colour) override;
	const bool checkCollision(const Sprite & sprite) override;
	Blockade& operator=(const Blockade& rhs) {
		destination = rhs.destination;
		PlayArea = rhs.PlayArea;
		active = rhs.active;
		health = rhs.health;
		ship = rhs.ship;
		deltaTime = rhs.deltaTime;
		colour = rhs.colour;
		bulletTimer = rhs.bulletTimer;
		speed = rhs.speed;
		Velocity = rhs.Velocity;
		bullets = rhs.bullets;
		return *this;
	}
};

