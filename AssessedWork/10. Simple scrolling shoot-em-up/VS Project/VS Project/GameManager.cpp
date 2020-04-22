#include "GameManager.h"

const void GameManager::cacheTextures()
{
	//load in any images
	d3d.GetCache().LoadTexture(&d3d.GetDevice(), "menu.dds");
	d3d.GetCache().LoadTexture(&d3d.GetDevice(), "end.dds");
	d3d.GetCache().LoadTexture(&d3d.GetDevice(), "ship.dds");
	d3d.GetCache().LoadTexture(&d3d.GetDevice(), "backgrounds/noalpha.dds");
	d3d.GetCache().LoadTexture(&d3d.GetDevice(), "backgrounds/star1alpha.dds");
	d3d.GetCache().LoadTexture(&d3d.GetDevice(), "backgrounds/star2alpha.dds");
}




const void GameManager::startGameLoop()
{
	while (WindowUtils::Get().BeginLoop(canUpdateRender))
	{
		if (canUpdateRender && deltaTime > 0)
		{
			update();
			render();
		}
		deltaTime = WindowUtils::Get().EndLoop(canUpdateRender);
	}
}


void GameManager::update()
{
	GamepadInput.Update();
	switch (currentState)
	{
	case GameManager::Menu:
		menuState::Get().update(deltaTime);
		break;
	case GameManager::Playing:
		playState::Get().update(deltaTime, d3d);
		break;
	case GameManager::Lost:
		endState::Get().update(deltaTime, d3d);
		break;
	default:
		break;
	}
}

const void GameManager::render()
{
	d3d.BeginRender(Colours::Black);
	DirectX::CommonStates dxstate(&d3d.GetDevice());
	spriteBatch->Begin(DirectX::SpriteSortMode_Deferred, dxstate.NonPremultiplied(), &d3d.GetWrapSampler());
	switch (currentState)
	{
	case GameManager::Menu:
		menuState::Get().render(d3d, spriteBatch);
		break;
	case GameManager::Playing:
		playState::Get().render(d3d, *spriteBatch);
		break;
	case GameManager::Lost:
		endState::Get().render(d3d, spriteBatch);
		break;
	default:
		break;
	}

	spriteBatch->End();
	d3d.EndRender();
	mouseAndKeyInput.PostProcess();
}
