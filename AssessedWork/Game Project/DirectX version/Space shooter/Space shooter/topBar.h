#pragma once
#include"Sprite.h"
#include"Text.h"
#include"Player.h"
#include"Boss.h"
#include"gameData.h"
class topBar
{
private:
	float initialPlayerHealth;
	float initialCompletionRate;
	Text playerHealth;
	Text levelCompletion;
	Sprite spr;
	DirectX::SpriteBatch& _spritebatch;
	d3d& _d3d;
public:
	topBar(d3d& d3d_, DirectX::SpriteBatch& spritebatch_) : _d3d(d3d_), _spritebatch(spritebatch_),
	levelCompletion(_d3d, "retro.spritefont"), playerHealth(_d3d, "retro.spritefont"), spr(d3d_) {
		spr.SetTex(*_d3d.GetCache().Get("TopBar").pTex);
		spr.SetScale(DirectX::SimpleMath::Vector2(gameData::Get().WindowSize.x / gameData::Get().MaxWindowSize.x, gameData::Get().WindowSize.y / gameData::Get().MaxWindowSize.y));
	}
	const void init() {
		spr.SetPosition(DirectX::SimpleMath::Vector2(0, 0));
		initialPlayerHealth = Player::Get().getHealth();
		initialCompletionRate = Boss::Get().getHealth();
		levelCompletion.setString(("Completion: " + std::to_string((int)(Boss::Get().getHealth() / initialCompletionRate * 100)) + "%"));
		playerHealth.SetPosition(DirectX::SimpleMath::Vector2(0, 0));
		levelCompletion.SetPosition(DirectX::SimpleMath::Vector2(gameData::Get().WindowSize.x - levelCompletion.getSize().x*(gameData::Get().WindowSize.x / gameData::Get().MaxWindowSize.x), 0));

		levelCompletion.SetScale(DirectX::SimpleMath::Vector2(gameData::Get().WindowSize.x / gameData::Get().MaxWindowSize.x, gameData::Get().WindowSize.y / gameData::Get().MaxWindowSize.y));
		playerHealth.SetScale(DirectX::SimpleMath::Vector2(gameData::Get().WindowSize.x / gameData::Get().MaxWindowSize.x, gameData::Get().WindowSize.y / gameData::Get().MaxWindowSize.y));
	}

	const void update() {
		playerHealth.setString(("Player Health: " + std::to_string((int)(Player::Get().getHealth()/ initialPlayerHealth * 100)) + "%"));
		levelCompletion.setString(("Completion: " + std::to_string((int)(100-(Boss::Get().getHealth()/ initialCompletionRate * 100))) + "%"));
	};
	const void render() {
		spr.Draw(_spritebatch);
		playerHealth.Draw(_spritebatch);
		levelCompletion.Draw(_spritebatch);
	};

};

