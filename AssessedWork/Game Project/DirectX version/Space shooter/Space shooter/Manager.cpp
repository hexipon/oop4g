#include "Manager.h"

MouseKeys Manager::mouseAndKeyInput;
Gamepad Manager::GamepadInput;
const void Manager::changeState(const gameStates & _state)
{
	switch (_state)
	{
	case gameStates::GameMenu :
		switch (currentState)
		{
		case gameStates::GameInstructions:
		case gameStates::GameSettings:
			delete states.back();
			states.pop_back();
			break;
		case gameStates::PausedGame:
			delete states.back();
			states.pop_back();
		case gameStates::EndGame:
			delete states.back();
			states.pop_back();
		default:
			states.push_back(new Menu(d3d, spriteBatch, deltaTime));
			break;
		}
		break;
	case gameStates::GameInstructions :
		states.push_back(new Instructions(d3d, spriteBatch, deltaTime));
		break;
	case gameStates::GameSettings :
		states.push_back(new Settings(d3d, spriteBatch, deltaTime));
		break;
	case gameStates::PlayingGame :
		delete states.back();
		states.pop_back();
		if(currentState == gameStates::GameMenu || currentState == gameStates::EndGame)
			states.push_back(new Playing(d3d, spriteBatch, deltaTime));
		break;
	case gameStates::PausedGame :
		states.push_back(new Pause(d3d, spriteBatch, deltaTime));
		break;
	case gameStates::EndGame :
		delete states.back();
		states.pop_back();
		states.push_back(new End(d3d, spriteBatch, deltaTime));
		break;
	default:
		break;
	}
	currentState = _state;
	return void();
}

const void Manager::startGameLoop()
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
	return void();
}

const void Manager::update()
{
	GamepadInput.Update();
	states.back()->update();
	return void();
}

const void Manager::render()
{
	d3d.BeginRender(Colours::Black);
	DirectX::CommonStates dxstate(&d3d.GetDevice());
	spriteBatch.Begin(DirectX::SpriteSortMode_Deferred, dxstate.NonPremultiplied(), &d3d.GetWrapSampler());

	if (currentState == PausedGame)
		states.front()->render();
	states.back()->render();

	spriteBatch.End();
	d3d.EndRender();
	mouseAndKeyInput.PostProcess();
	return void();
}
