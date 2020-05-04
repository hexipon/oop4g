#include "Pause.h"
#include"Manager.h"

void Pause::update()
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

void Pause::render()
{
	background.Draw(_spriteBatch);
	gameName.Draw(_spriteBatch);

	for (unsigned int i = 0; i < menuItems->size(); i++)
		menuItems->at(i).Draw(_spriteBatch);
}

void Pause::sizeSetup()
{
	background.SetScale({ gameData::Get().WindowSize.x / gameData::Get().MaxWindowSize.x,gameData::Get().WindowSize.y / gameData::Get().MaxWindowSize.y });
	gameName.SetPosition({ 0, gameData::Get().WindowSize.y*0.17f });
	gameName.SetScale({ gameData::Get().WindowSize.x / gameData::Get().MaxWindowSize.x,gameData::Get().WindowSize.y / gameData::Get().MaxWindowSize.y });
	menuItems->at(Continue).SetScale({ gameData::Get().WindowSize.x / gameData::Get().MaxWindowSize.x,gameData::Get().WindowSize.y / gameData::Get().MaxWindowSize.y });
	menuItems->at(Exit).SetScale({ gameData::Get().WindowSize.x / gameData::Get().MaxWindowSize.x,gameData::Get().WindowSize.y / gameData::Get().MaxWindowSize.y });
	menuItems->at(Exit).SetPosition(DirectX::SimpleMath::Vector2(gameData::Get().WindowSize.x / 15, gameData::Get().WindowSize.y*0.7f + (menuItems->at(Exit).getSize().y*menuItems->at(Exit).GetScale().y*Exit*1.2f)));
	menuItems->at(Menu).SetScale({ gameData::Get().WindowSize.x / gameData::Get().MaxWindowSize.x,gameData::Get().WindowSize.y / gameData::Get().MaxWindowSize.y });
	menuItems->at(Menu).SetPosition(DirectX::SimpleMath::Vector2(gameData::Get().WindowSize.x / 15, gameData::Get().WindowSize.y*0.7f + (menuItems->at(Menu).getSize().y*menuItems->at(Menu).GetScale().y*Menu*1.2f)));
	menuItems->at(Continue).SetPosition(DirectX::SimpleMath::Vector2(gameData::Get().WindowSize.x / 15, gameData::Get().WindowSize.y*0.7f + (menuItems->at(Continue).getSize().y*menuItems->at(Continue).GetScale().y*Continue*1.2f)));

}

const void Pause::enterPressed()
{
	switch (currentlySelected) {
	case Continue:
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

const void Pause::upPressed()
{
	switch (currentlySelected) {
	case Menu:
		currentlySelected = Continue;
		break;
	case Exit:
		currentlySelected = Menu;
		break;
	default:
		break;
	}
	return void();
}

const void Pause::downPressed()
{
	switch (currentlySelected) {
	case Continue:
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

const void Pause::colourChange()
{
	switch (currentlySelected)
	{
	case Pause::Continue:
		menuItems->at(Continue).SetColour(Colours::Green);
		menuItems->at(Menu).SetColour(Colours::White);
		break;
	case Pause::Menu:
		menuItems->at(Continue).SetColour(Colours::White);
		menuItems->at(Menu).SetColour(Colours::Green);
		menuItems->at(Exit).SetColour(Colours::White);
		break;
	case Pause::Exit:
		menuItems->at(Exit).SetColour(Colours::Green);
		menuItems->at(Menu).SetColour(Colours::White);
		break;
	default:
		break;
	}
	return void();
}
