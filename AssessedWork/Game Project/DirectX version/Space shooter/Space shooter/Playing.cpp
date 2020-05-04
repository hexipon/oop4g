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
	player.update();
	bar.update();
	
	for (auto& enemy : Enemies)
		enemy->update();
	for (auto& bullet : enemyBullets)
	{
		if (bullet.active)
		{
			if (player.checkCollision(bullet.getSprite()))
			{
				bullet.hasCollided();
				player.hasCollided(bullet.getColour());
			}
			bullet.Update();
		}
	}
	for (auto& bullet : playerBullets)
	{
		if (bullet.active)
		{
			for (auto& enemy : Enemies)
			{
				if (enemy->checkCollision(bullet.getSprite()))
				{
					bullet.hasCollided();
					enemy->hasCollided(bullet.getColour());
				}
			}
			bullet.Update();
		}
	}
	return void();
}

void Playing::render()
{
	for (auto& background : backgrounds)
		background.Draw(_spriteBatch);
	player.render();
	for (auto& enemy : Enemies)
		enemy->render();
	for (auto& bullet : enemyBullets)
		if(bullet.active)
			bullet.Render();
	for (auto& bullet : playerBullets)
		if(bullet.active)
			bullet.Render();
	bar.render();
	return void();
}
