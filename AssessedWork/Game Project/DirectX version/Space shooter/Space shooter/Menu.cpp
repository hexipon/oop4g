#include "Menu.h"
#include"Manager.h"

void Menu::update()
{
	if (selectionChangeCooldownTimer >= selectionChangeCooldown)
	{
	const bool _enterPressed =
		Manager::GamepadInput.IsPressed(0, XINPUT_GAMEPAD_B) ||
		Manager::mouseAndKeyInput.IsPressed(VK_RETURN);

		DBOUT("left stick x=" << Manager::GamepadInput.GetState(0).leftStickX << " y=" << Manager::GamepadInput.GetState(0).leftStickY);
		const bool _upPressed =
			Manager::mouseAndKeyInput.IsPressed(VK_W) ||
			Manager::mouseAndKeyInput.IsPressed(VK_UP) ||
			Manager::GamepadInput.IsPressed(0, XINPUT_GAMEPAD_DPAD_UP) ||
			(Manager::GamepadInput.GetState(0).leftStickY > 0);

		const bool _downPressed =
			Manager::mouseAndKeyInput.IsPressed(VK_S) ||
			Manager::mouseAndKeyInput.IsPressed(VK_DOWN) ||
		Manager::GamepadInput.IsPressed(0, XINPUT_GAMEPAD_DPAD_DOWN) ||
			(Manager::GamepadInput.GetState(0).leftStickY < 0);

	if (_enterPressed)
	{
		enterPressed();
		selectionChangeCooldownTimer = 0;
	}
		if (_upPressed || _downPressed)
		{
			if (_downPressed)
				downPressed();
			if (_upPressed)
				upPressed();
			changeColours();
			selectionChangeCooldownTimer = 0;
		}
	}
	else
	{
		selectionChangeCooldownTimer += _deltaTime;
	}

	for(unsigned int i=0; i<background->size();)
		background->at(i).Scroll((_deltaTime*++i) * 20, 0);

	return void();
}

void Menu::render()
{
	for (unsigned int i = 0; i < background->size(); i++)
		background->at(i).Draw(_spriteBatch);

	gameName.Draw(_spriteBatch);

	for (unsigned int i = 0; i < menuItems->size(); i++)
		menuItems->at(i).Draw(_spriteBatch);
	return void();
}

void Menu::sizeSetup() {
	background->at(0).SetScale({ gameData::Get().WindowSize.x / gameData::Get().MaxWindowSize.x,gameData::Get().WindowSize.y / gameData::Get().MaxWindowSize.y });

	background->at(1).SetScale({ gameData::Get().WindowSize.x / gameData::Get().MaxWindowSize.x,gameData::Get().WindowSize.y / gameData::Get().MaxWindowSize.y });

	gameName.SetScale({ gameData::Get().WindowSize.x / gameData::Get().MaxWindowSize.x,gameData::Get().WindowSize.y / gameData::Get().MaxWindowSize.y });
	gameName.SetPosition({ 0, gameData::Get().WindowSize.y*0.17f });

	menuItems->at(Play).SetScale({ gameData::Get().WindowSize.x / gameData::Get().MaxWindowSize.x,gameData::Get().WindowSize.y / gameData::Get().MaxWindowSize.y });
	menuItems->at(Play).SetPosition(DirectX::SimpleMath::Vector2(gameData::Get().WindowSize.x / 15, (gameData::Get().WindowSize.y / 2) + (menuItems->at(Play).getSize().y*menuItems->at(Play).GetScale().y*Play*1.2f)));

	menuItems->at(Instructions).SetScale({ gameData::Get().WindowSize.x / gameData::Get().MaxWindowSize.x,gameData::Get().WindowSize.y / gameData::Get().MaxWindowSize.y });
	menuItems->at(Instructions).SetPosition(DirectX::SimpleMath::Vector2(gameData::Get().WindowSize.x / 15, (gameData::Get().WindowSize.y / 2) + (menuItems->at(Instructions).getSize().y*menuItems->at(Instructions).GetScale().y*Instructions*1.2f)));

	menuItems->at(Settings).SetScale({ gameData::Get().WindowSize.x / gameData::Get().MaxWindowSize.x,gameData::Get().WindowSize.y / gameData::Get().MaxWindowSize.y });
	menuItems->at(Settings).SetPosition(DirectX::SimpleMath::Vector2(gameData::Get().WindowSize.x / 15, (gameData::Get().WindowSize.y / 2)+ (menuItems->at(Settings).getSize().y*menuItems->at(Settings).GetScale().y*Settings*1.2f)));

	menuItems->at(Exit).SetScale({ gameData::Get().WindowSize.x / gameData::Get().MaxWindowSize.x,gameData::Get().WindowSize.y / gameData::Get().MaxWindowSize.y });
	menuItems->at(Exit).SetPosition(DirectX::SimpleMath::Vector2(gameData::Get().WindowSize.x / 15, (gameData::Get().WindowSize.y / 2) + (menuItems->at(Exit).getSize().y*menuItems->at(Exit).GetScale().y*Exit*1.2f)));
}

const void Menu::enterPressed()
{
	switch (currentlySelected) {
	case Play:
		Manager::Get().changeState(Manager::gameStates::PlayingGame);
		break;
	case Instructions:
		Manager::Get().changeState(Manager::gameStates::GameInstructions);
		break;
	case Settings:
		Manager::Get().changeState(Manager::gameStates::GameSettings);
		break;
	case Exit:
		PostQuitMessage(0);
		break;
	default:
		break;
	}
	return void();
}

const void Menu::upPressed()
{
	switch (currentlySelected)
	{
	case Instructions:
		currentlySelected = Play;
		break;
	case Settings:
		currentlySelected = Instructions;
		break;
	case Exit:
		currentlySelected = Settings;
		break;
	default:
		break;
	}
	return void();
}

const void Menu::downPressed()
{
	switch (currentlySelected)
	{
	case Play:
		currentlySelected = Instructions;
		break;
	case Instructions:
		currentlySelected = Settings;
		break;
	case Settings:
		currentlySelected = Exit;
		break;
	default:
		break;
	}
	return void();
}

const void Menu::changeColours()
{
	switch (currentlySelected) {
	case Play:
		menuItems->at(Play).SetColour(Colours::Green);
		menuItems->at(Instructions).SetColour(Colours::White);
		break;
	case Instructions:
		menuItems->at(Play).SetColour(Colours::White);
		menuItems->at(Instructions).SetColour(Colours::Green);
		menuItems->at(Settings).SetColour(Colours::White);
		break;
	case Settings:
		menuItems->at(Instructions).SetColour(Colours::White);
		menuItems->at(Settings).SetColour(Colours::Green);
		menuItems->at(Exit).SetColour(Colours::White);
		break;
	case Exit:
		menuItems->at(Settings).SetColour(Colours::White);
		menuItems->at(Exit).SetColour(Colours::Green);
		break;
	default:
		break;
	}
	return void();
}
