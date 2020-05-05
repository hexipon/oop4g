#pragma once
#include <time.h>
#include"d3d.h"
#include"SpriteBatch.h"
#include"Player.h"
#include"State.h"
#include"Boss.h"
#include"topBar.h"
#include"powerUp.h"
#include"Blockade.h"
#include"Enemy.h"
#include"Enemy2.h"
class Playing : public State
{
private:
	DirectX::SimpleMath::Vector4 PlayArea;
	Player player;
	const int BGND_LAYERS = 3;
	std::vector<Sprite> backgrounds;
	std::vector<Bullet> playerBullets;
	std::vector<Bullet> enemyBullets;
	std::vector<Ship*> Enemies;
	std::vector<powerUp> powerUps;
	const void updateBackground();
	topBar bar;
	const float powerUpRate = 5.f;
	float powerUpTimer = powerUpRate;
	const float blockadeRate = 10.f;
	float blockadeTimer = blockadeRate;
	const float enemy1Rate = 20.f;
	float enemy1Timer = enemy1Rate;
	const float enemy2Rate = 40.f;
	float enemy2Timer = enemy2Rate;

public:
	Playing(d3d& d3d_, DirectX::SpriteBatch& spritebatch_, float& deltaTime_) : 
		State(d3d_, spritebatch_, deltaTime_),
		player(_d3d, _spriteBatch,_deltaTime, PlayArea, playerBullets),
		bar(_d3d,_spriteBatch) {
		int w, h;
		WindowUtils::Get().GetClientExtents(w, h);
		PlayArea.w = 0;
		PlayArea.x = h*0.0925f;
		PlayArea.y = (float)w*0.5f;
		PlayArea.z = (float)h;
		
		//setup boss
		Enemies.push_back(new Boss(_d3d, _spriteBatch, _deltaTime, PlayArea, enemyBullets));
		Enemies.back()->init();
		bar.init();
		backgrounds.insert(backgrounds.begin(), BGND_LAYERS, Sprite(_d3d));
		backgrounds[0].SetTex(*_d3d.GetCache().Get("staticBackground").pTex);
		backgrounds[1].SetTex(*_d3d.GetCache().Get("star1alpha").pTex);
		backgrounds[2].SetTex(*_d3d.GetCache().Get("star2alpha").pTex);
		sizeSetup();
		srand((unsigned int)time(NULL));
	}
	~Playing() {
		for (auto& enemy : Enemies)
		{
			delete enemy;
			enemy = nullptr;
		}
		Enemies.clear();
	}
	void update() override;
	void render() override;
	void sizeSetup() override {
		backgrounds[0].SetScale({ gameData::Get().WindowSize.x / gameData::Get().MaxWindowSize.x,gameData::Get().WindowSize.y / gameData::Get().MaxWindowSize.y });
		backgrounds[1].SetScale({ gameData::Get().WindowSize.x / gameData::Get().MaxWindowSize.x,gameData::Get().WindowSize.y / gameData::Get().MaxWindowSize.y });
		backgrounds[2].SetScale({ gameData::Get().WindowSize.x / gameData::Get().MaxWindowSize.x,gameData::Get().WindowSize.y / gameData::Get().MaxWindowSize.y });
	};
	void spawnPowerUp();
	void spawnBlockade();
	void spawnEnemy1();
	void spawnEnemy2();

};

