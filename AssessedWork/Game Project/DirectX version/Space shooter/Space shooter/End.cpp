#include "End.h"
#include"Manager.h"

void End::update()
{
	if (selectionChangeCooldownTimer >= selectionChangeCooldown)
	{
		const bool _upPressed =
			Manager::mouseAndKeyInput.IsPressed(VK_W) || Manager::mouseAndKeyInput.IsPressed(VK_UP) ||
			Manager::GamepadInput.IsPressed(0, XINPUT_GAMEPAD_DPAD_UP) || (Manager::GamepadInput.GetState(0).leftStickY > 0);

		const bool _downPressed =
			Manager::mouseAndKeyInput.IsPressed(VK_S) || Manager::mouseAndKeyInput.IsPressed(VK_DOWN) ||
			Manager::GamepadInput.IsPressed(0, XINPUT_GAMEPAD_DPAD_DOWN) || (Manager::GamepadInput.GetState(0).leftStickY < 0);

		if (_upPressed || _downPressed)
		{
			if (_downPressed)
				downPressed();
			if (_upPressed)
				upPressed();
			colourChange();
			selectionChangeCooldownTimer = 0;
		}
	}
	else
	{
		selectionChangeCooldownTimer += _deltaTime;
	}
	const bool _enterPressed =
		Manager::GamepadInput.IsPressed(0, XINPUT_GAMEPAD_B) ||
		Manager::mouseAndKeyInput.IsPressed(VK_RETURN);
	if (_enterPressed)
		enterPressed();
}

void End::render()
{
	background.Draw(_spriteBatch);
	gameName.Draw(_spriteBatch);

	for (unsigned int i = 0; i < menuItems->size(); i++)
		menuItems->at(i).Draw(_spriteBatch);
}

void End::sizeSetup()
{
	background.SetScale({ gameData::Get().WindowSize.x / gameData::Get().MaxWindowSize.x,gameData::Get().WindowSize.y / gameData::Get().MaxWindowSize.y });
	gameName.SetPosition({ 0, gameData::Get().WindowSize.y*0.17f });
	gameName.SetScale({ gameData::Get().WindowSize.x / gameData::Get().MaxWindowSize.x,gameData::Get().WindowSize.y / gameData::Get().MaxWindowSize.y });
	menuItems->at(PlayAgain).SetScale({ gameData::Get().WindowSize.x / gameData::Get().MaxWindowSize.x,gameData::Get().WindowSize.y / gameData::Get().MaxWindowSize.y });
	menuItems->at(Exit).SetScale({ gameData::Get().WindowSize.x / gameData::Get().MaxWindowSize.x,gameData::Get().WindowSize.y / gameData::Get().MaxWindowSize.y });
	menuItems->at(Exit).SetPosition(DirectX::SimpleMath::Vector2(gameData::Get().WindowSize.x / 15, gameData::Get().WindowSize.y*0.7f + (menuItems->at(Exit).getSize().y*menuItems->at(Exit).GetScale().y*Exit*1.2f)));
	menuItems->at(Menu).SetScale({ gameData::Get().WindowSize.x / gameData::Get().MaxWindowSize.x,gameData::Get().WindowSize.y / gameData::Get().MaxWindowSize.y });
	menuItems->at(Menu).SetPosition(DirectX::SimpleMath::Vector2(gameData::Get().WindowSize.x / 15, gameData::Get().WindowSize.y*0.7f + (menuItems->at(Menu).getSize().y*menuItems->at(Menu).GetScale().y*Menu*1.2f)));
	menuItems->at(PlayAgain).SetPosition(DirectX::SimpleMath::Vector2(gameData::Get().WindowSize.x / 15, gameData::Get().WindowSize.y*0.7f + (menuItems->at(PlayAgain).getSize().y*menuItems->at(PlayAgain).GetScale().y*PlayAgain*1.2f)));

}

const void End::enterPressed()
{
	switch (currentlySelected) {
	case PlayAgain:
		Manager::Get().changeState(Manager::gameStates::PlayingGame);
		break;
	case Menu:
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

const void End::upPressed()
{
	switch (currentlySelected) {
	case Menu:
		currentlySelected = PlayAgain;
		break;
	case Exit:
		currentlySelected = Menu;
		break;
	default:
		break;
	}
	return void();
}

const void End::downPressed()
{
	switch (currentlySelected) {
	case PlayAgain:
		currentlySelected = Menu;
		break;
	case Menu:
		currentlySelected = Exit;
		break;
	default:
		break;
	}
	return void();
}

const void End::colourChange()
{
	switch (currentlySelected)
	{
	case PlayAgain:
		menuItems->at(PlayAgain).SetColour(Colours::Green);
		menuItems->at(Menu).SetColour(Colours::White);
		break;
	case Menu:
		menuItems->at(PlayAgain).SetColour(Colours::White);
		menuItems->at(Menu).SetColour(Colours::Green);
		menuItems->at(Exit).SetColour(Colours::White);
		break;
	case Exit:
		menuItems->at(Exit).SetColour(Colours::Green);
		menuItems->at(Menu).SetColour(Colours::White);
		break;
	default:
		break;
	}
	return void();
}
