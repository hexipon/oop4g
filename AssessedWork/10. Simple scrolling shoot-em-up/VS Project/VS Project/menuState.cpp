#include "menuState.h"
#include"GameManager.h"

void menuState::update(const float & deltaTime)
{
	if (GameManager::Get().mouseAndKeyInput.IsPressed(VK_SPACE))
	{
		GameManager::Get().changeState(GameManager::gameStates::Playing);
	}
}

void menuState::render(d3d & d3d, DirectX::SpriteBatch * spritebatch)
{
	Sprite spr(d3d);
	spr.SetTex(*d3d.GetCache().Get("menu").pTex);
	spr.Draw(*spritebatch);
}
