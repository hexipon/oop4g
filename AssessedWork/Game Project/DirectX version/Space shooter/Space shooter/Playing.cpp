#include "Playing.h"
#include"Manager.h"

const void Playing::updateBackground()
{
	int i = 0;
	for (auto& background : backgrounds)
		background.Scroll((_deltaTime*(i++)) * 20, 0);
	return void();
}

void Playing::update()
{
	const bool _PausePressed =
		Manager::mouseAndKeyInput.IsPressed(VK_P) ||
		Manager::GamepadInput.IsPressed(0, XINPUT_GAMEPAD_START);

	if (_PausePressed)
		Manager::Get().changeState(Manager::gameStates::PausedGame);

	updateBackground();
	if(player.active)
		player.update();
	bar.update();
	
	for (auto& enemy : Enemies)
		if(enemy->active)
			enemy->update();
	for (auto& bullet : enemyBullets)
	{
				if (player.checkCollision(bullet.getSprite()))
				{
					bullet.hasCollided();
					player.hasCollided(bullet.getColour());
				}
			bullet.Update();
	}
	for (auto& bullet : playerBullets)
	{
			for (auto& enemy : Enemies)
			{
				if (enemy->active)
				{
					if (enemy->checkCollision(bullet.getSprite()))
					{
						bullet.hasCollided();
						enemy->hasCollided(bullet.getColour());
					}
				}
			}
			bullet.Update();
	}
	for (auto& powerup : powerUps)
		{
			if (Player::Get().checkCollision(powerup.GetSprite()))
			{
				powerup.hasCollidedWithPlayer();
			}
			if (powerup.checkCollision(Boss::Get().GetSprite()))
			{
				powerup.hasCollided(Boss::Get().GetColour());
			}
			for (auto& bullet : playerBullets)
			{
				if (powerup.checkCollision(bullet.getSprite()))
				{
					powerup.hasCollided(bullet.getColour());
				}
			}
			for (auto& bullet : enemyBullets)
			{
				if (powerup.checkCollision(bullet.getSprite()))
				{
					powerup.hasCollided(bullet.getColour());
				}
			}
			powerup.update();
		}
		for (unsigned int i = 0; i < playerBullets.size(); i++)
	{
		if (playerBullets[i].active == false)
			playerBullets.erase(playerBullets.begin() + i);
	}
	for (unsigned int i = 0; i < enemyBullets.size(); i++)
	{
		if (enemyBullets[i].active == false)
			enemyBullets.erase(enemyBullets.begin() + i);
	}
	for (unsigned int i = 0; i < powerUps.size(); i++)
	{
		if (powerUps[i].active == false)
			powerUps.erase(powerUps.begin() + i);
	}


    spawnPowerUp();
	if (GetClock() > 30.f)
		spawnBlockade();
	if (GetClock() > 60.f)
		spawnEnemy1();
	if (GetClock() > 120.f)
		spawnEnemy2();

	if (player.getHealth() <= 0 || Boss::Get().getHealth() <=0)
	{
		Manager::Get().changeState(Manager::gameStates::EndGame);
	}



	return void();
}

void Playing::render()
{
	for (auto& background : backgrounds)
		background.Draw(_spriteBatch);
	player.render();
	for (auto& enemy : Enemies)
		if(enemy->active)
			enemy->render();
	for (auto& bullet : enemyBullets)
			bullet.Render();
	for (auto& bullet : playerBullets)
			bullet.Render();
	for (auto& powerup : powerUps)
		powerup.render();
	bar.render();
	return void();
}

void Playing::spawnPowerUp()
{
	if (powerUpTimer <= 0.f)
	{
		const int h = rand() % 2;
		int mode = (rand() % 6);
		powerUps.push_back(powerUp(_d3d, _spriteBatch, _deltaTime, PlayArea, mode));
		mode = rand() % (int)PlayArea.y;
		powerUps.back().setPostion(DirectX::SimpleMath::Vector2((float)mode, ((h == 1) ? (0.f) : (PlayArea.z))));
		mode = rand() % (int)PlayArea.y;
		powerUps.back().setDestination(DirectX::SimpleMath::Vector2((float)mode, ((h == 1) ? (PlayArea.z + 20.f) : (-20.f))));
		powerUpTimer = powerUpRate;
	}
	powerUpTimer -= _deltaTime;
}

void Playing::spawnBlockade()
{
	if (blockadeTimer <= 0.f)
	{
		const int h = rand() % 2;
		const int mode = (rand() % 6);
		Enemies.push_back(new Blockade(_d3d, _spriteBatch, _deltaTime, PlayArea, mode));


		const float xpos = (Boss::Get().GetSprite().GetPosition().x - Boss::Get().GetSprite().GetScreenSize().x / 2);
		Enemies.back()->setPostion(DirectX::SimpleMath::Vector2(xpos, ((h == 1) ? (0.f) : (PlayArea.z))));
		Enemies.back()->setDestination(DirectX::SimpleMath::Vector2((float)xpos, ((h == 1) ? (PlayArea.z) : (0.f))));
		blockadeTimer = blockadeRate;
	}
	blockadeTimer -= _deltaTime;
}

void Playing::spawnEnemy1()
{

	if (enemy1Timer <= 0.f)
	{
		const int h = rand() % 2;
		const int mode = (rand() % 6);
		Enemies.push_back(new Enemy(_d3d, _spriteBatch, _deltaTime, PlayArea,enemyBullets, mode));


		const float xpos = (Boss::Get().GetSprite().GetPosition().x - Boss::Get().GetSprite().GetScreenSize().x);
		Enemies.back()->setPostion(DirectX::SimpleMath::Vector2((float)xpos, ((h == 1) ? (0.f) : (PlayArea.z))));
		Enemies.back()->setDestination(DirectX::SimpleMath::Vector2((float)xpos, ((h == 1) ? (PlayArea.z) : (0.f))));

		enemy1Timer = enemy1Rate;
	}
	enemy1Timer -= _deltaTime;
}

void Playing::spawnEnemy2()
{
	if (enemy2Timer <= 0.f)
	{
		const int h = rand() % 2;
		const int mode = (rand() % 6);
		Enemies.push_back(new Enemy2(_d3d, _spriteBatch, _deltaTime, PlayArea, enemyBullets, mode));


		const float xpos = (Boss::Get().GetSprite().GetPosition().x - Boss::Get().GetSprite().GetScreenSize().x*1.5f);
		Enemies.back()->setPostion(DirectX::SimpleMath::Vector2((float)xpos, ((h == 1) ? (0.f) : (PlayArea.z))));
		Enemies.back()->setDestination(DirectX::SimpleMath::Vector2((float)xpos, ((h == 1) ? (PlayArea.z) : (0.f))));

		enemy2Timer = enemy2Rate;
	}
	enemy2Timer -= _deltaTime;

}
