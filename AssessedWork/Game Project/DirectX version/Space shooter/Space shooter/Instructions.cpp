#include "Instructions.h"
#include"Manager.h"
void Instructions::update()
{
	if (selectionChangeCooldownTimer >= selectionChangeCooldown)
	{
		const bool _upPressed =
			Manager::mouseAndKeyInput.IsPressed(VK_W) || Manager::mouseAndKeyInput.IsPressed(VK_UP) ||
			Manager::GamepadInput.IsPressed(0, XINPUT_GAMEPAD_DPAD_UP) || (Manager::GamepadInput.GetState(0).leftStickY > 0);

		const bool _downPressed =
			Manager::mouseAndKeyInput.IsPressed(VK_S) || Manager::mouseAndKeyInput.IsPressed(VK_DOWN) ||
			Manager::GamepadInput.IsPressed(0, XINPUT_GAMEPAD_DPAD_DOWN) || (Manager::GamepadInput.GetState(0).leftStickY < 0);

	const bool _enterPressed =
		Manager::GamepadInput.IsPressed(0, XINPUT_GAMEPAD_B) ||
		Manager::mouseAndKeyInput.IsPressed(VK_RETURN);
	if (_enterPressed)
	{
		enterPressed();
		selectionChangeCooldownTimer = 0;
	}
		if (_upPressed || _downPressed)
		{
			if (_downPressed && currentlySelected == Back)
			{
				currentlySelected = Exit;
				menuItems->at(Back).SetColour(Colours::White);
				menuItems->at(Exit).SetColour(Colours::Green);
			}
			if (_upPressed && currentlySelected == Exit)
			{
				currentlySelected = Back;
				menuItems->at(Back).SetColour(Colours::Green);
				menuItems->at(Exit).SetColour(Colours::White);
			}
			selectionChangeCooldownTimer = 0;
		}
	}
	else
	{
		selectionChangeCooldownTimer += _deltaTime;
	}
}

void Instructions::render()
{
	background.Draw(_spriteBatch);
	gameName.Draw(_spriteBatch);

	for (unsigned int i = 0; i < menuItems->size(); i++)
		menuItems->at(i).Draw(_spriteBatch);
}

void Instructions::sizeSetup()
{
		background.SetScale({ gameData::Get().WindowSize.x / gameData::Get().MaxWindowSize.x,gameData::Get().WindowSize.y / gameData::Get().MaxWindowSize.y });
		gameName.SetPosition({ 0, gameData::Get().WindowSize.y*0.17f });
		gameName.SetScale({ gameData::Get().WindowSize.x / gameData::Get().MaxWindowSize.x,gameData::Get().WindowSize.y / gameData::Get().MaxWindowSize.y });
		menuItems->at(Back).SetScale({ gameData::Get().WindowSize.x / gameData::Get().MaxWindowSize.x,gameData::Get().WindowSize.y / gameData::Get().MaxWindowSize.y });
		menuItems->at(Exit).SetScale({ gameData::Get().WindowSize.x / gameData::Get().MaxWindowSize.x,gameData::Get().WindowSize.y / gameData::Get().MaxWindowSize.y });
		menuItems->at(Exit).SetPosition(DirectX::SimpleMath::Vector2(gameData::Get().WindowSize.x / 15, gameData::Get().WindowSize.y*0.7f + (menuItems->at(Exit).getSize().y*menuItems->at(Exit).GetScale().y*Exit*1.2f)));
		menuItems->at(Back).SetPosition(DirectX::SimpleMath::Vector2(gameData::Get().WindowSize.x / 15, gameData::Get().WindowSize.y*0.7f + (menuItems->at(Back).getSize().y*menuItems->at(Back).GetScale().y*Back*1.2f)));
}

const void Instructions::enterPressed()
{
	switch (currentlySelected) {
	case Back:
		Manager::Get().changeState(Manager::gameStates::GameMenu);
		break;
	case Exit:
		PostQuitMessage(0);
		break;
	default:
		break;
	}
	return void();
}
