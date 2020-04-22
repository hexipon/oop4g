#include "endState.h"
#include"GameManager.h"

void endState::update(const float & deltaTime, d3d& _d3d)
{
	if (GameManager::Get().mouseAndKeyInput.IsPressed(VK_RETURN))
	{
		playState::Get().reset(_d3d);
		GameManager::Get().changeState(GameManager::gameStates::Playing);
	}
}

void endState::render(d3d & d3d, DirectX::SpriteBatch * spritebatch)
{
	Sprite spr(d3d);
	spr.SetTex(*d3d.GetCache().Get("end").pTex);
	spr.Draw(*spritebatch);
	Score::Get().Render(*spritebatch);
}
