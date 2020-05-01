#include "PlayerShip.h"
#include"GameManager.h"
const void PlayerShip::Update(const float & deltaTime, const RECTF& PlayArea)
{
	//move the ship
	DirectX::SimpleMath::Vector2 pos{ GetPosition() };
	if (GameManager::mouseAndKeyInput.IsPressed(VK_W) || GameManager::mouseAndKeyInput.IsPressed(VK_UP))
		pos.y -= SPEED * deltaTime;
	else if (GameManager::mouseAndKeyInput.IsPressed(VK_S) || GameManager::mouseAndKeyInput.IsPressed(VK_DOWN))
		pos.y += SPEED * deltaTime;

		DBOUT("left stick x=" << GameManager::GamepadInput.GetState(0).leftStickY << " y=" << GameManager::GamepadInput.GetState(0).leftStickY);
		pos.y -= GameManager::GamepadInput.GetState(0).leftStickY * PAD_SPEED * deltaTime;

	//keep it within window
	if (pos.x < PlayArea.left)
		pos.x = PlayArea.left;
	else if (pos.x > PlayArea.right)
		pos.x = PlayArea.right;
	if (pos.y < PlayArea.top)
		pos.y = PlayArea.top;
	else if (pos.y > PlayArea.bottom)
		pos.y = PlayArea.bottom;
	SetPosition(pos);
	return void();
}
