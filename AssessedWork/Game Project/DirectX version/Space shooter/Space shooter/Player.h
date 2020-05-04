#pragma once
#include"Ship.h"
#include"Bullet.h"
#include"Shield.h"
#include"Singleton.h"
class Player : public Ship, public Singleton<Player>
{
private:
	float modeChangeCooldownTimer = 0.f;
	const float modeChangeCooldown = 0.2f;
	DirectX::SimpleMath::Vector4& PlayArea;
	const std::string textures[6]={ {"PGreen"},{"PBlue"},{"PPurple"},{"PRed"},{"POrange"},{"PYellow"} };
	std::vector<Bullet>& bullets;
	float missileTimer = 0.0f;
	const float missile_debounce = 0.15f;
	Shield shield;
	const float shieldLength = 10.f;
	const void colourChangeLeft();
	const void colourChangeRight();
	const void checkBorders();
	const void shoot();
public:
	Player(d3d& d3d_, DirectX::SpriteBatch& spritebatch_, float& deltaTime_,
		DirectX::SimpleMath::Vector4& _PlayArea, std::vector<Bullet>& _bullets) :
		Ship(d3d_, spritebatch_, deltaTime_), PlayArea(_PlayArea),
		shield(_d3d,_spritebatch,deltaTime), bullets(_bullets) {

		shield.changeMode(colour);
		shield.activate(10.f);

		ship.SetTex(*_d3d.GetCache().Get(textures[colour]).pTex);
		ship.SetScale(DirectX::SimpleMath::Vector2(gameData::Get().WindowSize.x / gameData::Get().MaxWindowSize.x, gameData::Get().WindowSize.y / gameData::Get().MaxWindowSize.y));

		int w, h;
		WindowUtils::Get().GetClientExtents(w, h);
		ship.SetPosition(DirectX::SimpleMath::Vector2(PlayArea.x, (h / 2) - (ship.GetScreenSize().y / 2.f)));
		health = 500.f;
	}
	const void render() override;
	const void update() override;
	const void hasCollided(const int _colour) override;
	const bool checkCollision(const Sprite & sprite) override;

	const void init() override{}
	const void activateShield() {
		shield.changeMode(colour);
		shield.activate(shieldLength);
	}
	const DirectX::SimpleMath::Vector2 getPosition() {
		return ship.GetPosition();
	}
	DirectX::SimpleMath::Vector2 GetScreenSize() const {
		return ship.GetScreenSize();
	}
};

