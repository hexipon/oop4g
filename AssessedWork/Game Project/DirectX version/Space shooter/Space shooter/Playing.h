#pragma once
#include"d3d.h"
#include"SpriteBatch.h"
#include"Player.h"
#include"State.h"
#include"Boss.h"
#include"topBar.h"
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
	const void updateBackground();
	topBar bar;

public:
	Playing(d3d& d3d_, DirectX::SpriteBatch& spritebatch_, float& deltaTime_) : 
		State(d3d_, spritebatch_, deltaTime_),
		player(_d3d, _spriteBatch,_deltaTime, PlayArea, playerBullets),
		bar(_d3d,_spriteBatch) {
		int w, h;
		WindowUtils::Get().GetClientExtents(w, h);
		PlayArea.w = 0;
		PlayArea.x = 0;
		PlayArea.y = w - PlayArea.w;
		PlayArea.z = h - player.GetScreenSize().y;

		//setup boss
		Enemies.push_back(new Boss(_d3d, _spriteBatch, _deltaTime, PlayArea, enemyBullets));
		Enemies.back()->init();
		bar.init();
		backgrounds.insert(backgrounds.begin(), BGND_LAYERS, Sprite(_d3d));
		backgrounds[0].SetTex(*_d3d.GetCache().Get("staticBackground").pTex);
		backgrounds[1].SetTex(*_d3d.GetCache().Get("star1alpha").pTex);
		backgrounds[2].SetTex(*_d3d.GetCache().Get("star2alpha").pTex);
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
	void sizeSetup() override {};

};

