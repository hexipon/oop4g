#pragma once
#include"Ship.h"
class Enemy2 : public Ship
{
private:
	DirectX::SimpleMath::Vector4& PlayArea;
	const std::string textures[6] = { {"E3Green"},{"E3Blue"},{"E3Purple"},{"E3Red"},{"E3Orange"},{"E3Yellow"} };
	std::vector<Bullet>& bullets;
	float missileTimer = 0.0f;
	const float guns1Distance = 10.f;
	const float guns2Distance = 40.f;
	const float missile_debounce = 0.3f;
	const void shoot();
public:
	Enemy2(d3d& d3d_, DirectX::SpriteBatch& spritebatch_, float& deltaTime_,
		DirectX::SimpleMath::Vector4& _PlayArea, std::vector<Bullet>& _bullets, const int type) :
		Ship(d3d_, spritebatch_, deltaTime_), PlayArea(_PlayArea),
		bullets(_bullets) {
		colour = Ship::colourType(type);
		ship.SetTex(*_d3d.GetCache().Get(textures[type]).pTex);
		ship.SetScale(DirectX::SimpleMath::Vector2(gameData::Get().WindowSize.x / gameData::Get().MaxWindowSize.x, gameData::Get().WindowSize.y / gameData::Get().MaxWindowSize.y));
		speed = 70.f;
		health = 20.f;

	}
	const void init() override {
	}
	const void render() override;
	const void update() override;
	const void hasCollided(const int _colour) override;
	const bool checkCollision(const Sprite & sprite) override;
};