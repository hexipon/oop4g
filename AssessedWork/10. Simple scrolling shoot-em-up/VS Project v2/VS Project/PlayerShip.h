#pragma once
#include"Sprite.h"
#include"SpriteBatch.h"
#include"SimpleMath.h"
class GameManager;
class PlayerShip
{
private:
	const float SPEED = 250;
	const float PAD_SPEED = 250;
	Sprite ship;
public:
	PlayerShip(d3d& _d3d) : ship(_d3d) {}
	const void Init(d3d& _d3d) {

		//load the ship
		ship.SetTex(*_d3d.GetCache().Get("ship").pTex);
		ship.SetScale(DirectX::SimpleMath::Vector2(0.2f, 0.2f));
	}
	const DirectX::SimpleMath::Vector2 GetPosition() {
		return ship.GetPosition();
	}
	const void SetPosition(const DirectX::SimpleMath::Vector2& newPos) {
		ship.SetPosition(newPos);
	}
	const DirectX::SimpleMath::Vector2 GetScreenSize() {
		return ship.GetScreenSize();
	}
	Sprite& GetSprite() {
		return ship;
	}
	const void Draw(DirectX::SpriteBatch & spritebatch) {
		ship.Draw(spritebatch);
	}
	const void Update(const float& deltaTime, const RECTF& PlayArea);
};

