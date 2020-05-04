#include "Settings.h"
#include"Manager.h"
#include"WindowUtils.h"

void Settings::update()
{
	if (selectionChangeCooldownTimer >= selectionChangeCooldown)
	{
		const bool _enterPressed =
			Manager::GamepadInput.IsPressed(0, XINPUT_GAMEPAD_B) ||
			Manager::mouseAndKeyInput.IsPressed(VK_RETURN);

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
}

void Settings::render()
{
	background.Draw(_spriteBatch);
	for (unsigned int i = 0; i < menuItems->size(); i++)
		menuItems->at(i).Draw(_spriteBatch);

}

void Settings::sizeSetup()
{
		background.SetScale({ gameData::Get().WindowSize.x / gameData::Get().MaxWindowSize.x,gameData::Get().WindowSize.y / gameData::Get().MaxWindowSize.y });
		menuItems->at(Back).SetScale({ gameData::Get().WindowSize.x / gameData::Get().MaxWindowSize.x,gameData::Get().WindowSize.y / gameData::Get().MaxWindowSize.y });
		menuItems->at(Resolution).SetScale({ gameData::Get().WindowSize.x / gameData::Get().MaxWindowSize.x,gameData::Get().WindowSize.y / gameData::Get().MaxWindowSize.y });
		menuItems->at(Comfirm).SetScale({ gameData::Get().WindowSize.x / gameData::Get().MaxWindowSize.x,gameData::Get().WindowSize.y / gameData::Get().MaxWindowSize.y });
		menuItems->at(Back).SetScale({ gameData::Get().WindowSize.x / gameData::Get().MaxWindowSize.x,gameData::Get().WindowSize.y / gameData::Get().MaxWindowSize.y });
		menuItems->at(Exit).SetScale({ gameData::Get().WindowSize.x / gameData::Get().MaxWindowSize.x,gameData::Get().WindowSize.y / gameData::Get().MaxWindowSize.y });
		menuItems->at(Resolution).SetPosition(DirectX::SimpleMath::Vector2(gameData::Get().WindowSize.x / 2 - ((menuItems->at(Resolution).getSize().x / 2)*menuItems->at(Resolution).GetScale().y), gameData::Get().WindowSize.y*0.7f + menuItems->at(Resolution).getSize().y*menuItems->at(Resolution).GetScale().y*Resolution));
		menuItems->at(Back).SetPosition(DirectX::SimpleMath::Vector2(gameData::Get().WindowSize.x / 2 - ((menuItems->at(Back).getSize().x / 2)*menuItems->at(Back).GetScale().y), gameData::Get().WindowSize.y*0.7f + menuItems->at(Back).getSize().y*menuItems->at(Back).GetScale().y*Back));
		menuItems->at(Comfirm).SetPosition(DirectX::SimpleMath::Vector2(gameData::Get().WindowSize.x / 2 - ((menuItems->at(Comfirm).getSize().x / 2)*menuItems->at(Comfirm).GetScale().y), gameData::Get().WindowSize.y*0.7f + menuItems->at(Comfirm).getSize().y*menuItems->at(Comfirm).GetScale().y*Comfirm));
		menuItems->at(Exit).SetPosition(DirectX::SimpleMath::Vector2(gameData::Get().WindowSize.x / 2 - ((menuItems->at(Exit).getSize().x / 2)*menuItems->at(Exit).GetScale().y), gameData::Get().WindowSize.y*0.7f + menuItems->at(Exit).getSize().y*menuItems->at(Exit).GetScale().y*Exit));
}

const void Settings::enterPressed()
{
	switch (currentlySelected)
	{
	case menuOption::Resolution:
		changeRes();
		break;
	case menuOption::Comfirm:
		gameData::Get().WindowSize = resolutions[selectedRes];
		Manager::Get().resChange();
		WindowUtils::Get().setClientSize((int)gameData::Get().WindowSize.x, (int)gameData::Get().WindowSize.y);
		_d3d.OnResize((int)gameData::Get().WindowSize.x, (int)gameData::Get().WindowSize.y, _d3d);
		Manager::Get().changeState(Manager::gameStates::GameMenu);
		break;
	case menuOption::Back:
		Manager::Get().changeState(Manager::gameStates::GameMenu);
		break;
	case menuOption::Exit:
		PostQuitMessage(0);
		break;
	default:
		break;

	}
	return void();
}

const void Settings::upPressed()
{
	switch (currentlySelected)
	{
	case Settings::Comfirm:
		currentlySelected = Resolution;
		break;
	case Settings::Back:
		currentlySelected = Comfirm;
		break;
	case Settings::Exit:
		currentlySelected = Back;
		break;
	default:
		break;
	}
	return void();
}

const void Settings::downPressed()
{
	switch (currentlySelected)
	{
	case Settings::Resolution:
		currentlySelected = Comfirm;
		break;
	case Settings::Comfirm:
		currentlySelected = Back;
		break;
	case Settings::Back:
		currentlySelected = Exit;
		break;
	default:
		break;
	}
	return void();
}

const void Settings::changeColours()
{
	switch (currentlySelected)
	{
	case Settings::Resolution:
		menuItems->at(Resolution).SetColour(Colours::Green);
		menuItems->at(Comfirm).SetColour(Colours::White);
		break;
	case Settings::Comfirm:
		menuItems->at(Resolution).SetColour(Colours::White);
		menuItems->at(Comfirm).SetColour(Colours::Green);
		menuItems->at(Back).SetColour(Colours::White);
		break;
	case Settings::Back:
		menuItems->at(Comfirm).SetColour(Colours::White);
		menuItems->at(Back).SetColour(Colours::Green);
		menuItems->at(Exit).SetColour(Colours::White);
		break;
	case Settings::Exit:
		menuItems->at(Exit).SetColour(Colours::Green);
		menuItems->at(Back).SetColour(Colours::White);
		break;
	default:
		break;
	}
	return void();
}

const void Settings::changeRes()
{
	
	switch (selectedRes)
	{
	case Settings::w768:
		selectedRes = w896;
		break;
	case Settings::w896:
		selectedRes = w1024;
		break;
	case Settings::w1024:
		selectedRes = w1152;
		break;
	case Settings::w1152:
		selectedRes = w1280;
		break;
	case Settings::w1280:
		selectedRes = w1408;
		break;
	case Settings::w1408:
		selectedRes = w1536;
		break;
	case Settings::w1536:
		selectedRes = w1664;
		break;
	case Settings::w1664:
		selectedRes = w1792;
		break;
	case Settings::w1792:
		selectedRes = w768;
		break;
	default:
		break;
	}
	menuItems->at(Resolution).setString(("Resolution:" + std::to_string((int)resolutions[selectedRes].x) + "x" + std::to_string((int)resolutions[selectedRes].y)).c_str());

	menuItems->at(Resolution).SetPosition(DirectX::SimpleMath::Vector2(gameData::Get().WindowSize.x / 2 - ((menuItems->at(Resolution).getSize().x / 2)*menuItems->at(Resolution).GetScale().y), gameData::Get().WindowSize.y*0.7f + menuItems->at(Resolution).getSize().y*menuItems->at(Resolution).GetScale().y*Resolution));
	return void();
}
