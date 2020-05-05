#pragma once
#include"Ship.h"
#include"Singleton.h"
#include "Player.h"
class Boss : public Ship, public Singleton<Boss>
{
private:
	float modeChangeCooldownTimer = 21.f;
	const float modeChangeCooldown = 20.f;
	DirectX::SimpleMath::Vector4& PlayArea;
	const std::string textures[6] = { {"BGREEN"},{"BBLUE"},{"BPURPLE"},{"BRED"},{"BORANGE"},{"BYELLOW"} };
	std::vector<Bullet>& bullets;
	float missileTimer = 0.0f;
	const float guns1Distance = 55.f;
	const float missile_debounce = 1.f;
	const void colourChange();
	const void shoot();
public:
	Boss(d3d& d3d_, DirectX::SpriteBatch& spritebatch_, float& deltaTime_,
		DirectX::SimpleMath::Vector4& _PlayArea, std::vector<Bullet>& _bullets) :
		Ship(d3d_, spritebatch_, deltaTime_), PlayArea(_PlayArea), 
	bullets(_bullets) {
		ship.SetTex(*_d3d.GetCache().Get(textures[colour]).pTex);
		ship.SetScale(DirectX::SimpleMath::Vector2(gameData::Get().WindowSize.x / gameData::Get().MaxWindowSize.x, gameData::Get().WindowSize.y / gameData::Get().MaxWindowSize.y));
		speed = 40.f;
		ship.SetPosition(DirectX::SimpleMath::Vector2(gameData::Get().WindowSize.x + ship.GetScreenSize().x * 1.5f, (PlayArea.z / 2) - (ship.GetScreenSize().y / 2.f)));
		health = 2300.f;
		
	}
	const void init() override{
		//set initial destination
		setDestination(DirectX::SimpleMath::Vector2(gameData::Get().WindowSize.x - ship.GetScreenSize().x - 20*(gameData::Get().WindowSize.x / gameData::Get().MaxWindowSize.x), ship.GetPosition().y));
	}
	const void render() override;
	const void update() override;
	const void hasCollided(const int _colour) override;
	const bool checkCollision(const Sprite & sprite) override;

};

