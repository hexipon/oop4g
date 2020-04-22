#include "GameManager.h"

const void GameManager::windowSetup()
{
	window.create(sf::VideoMode(GameData::SCREEN_RES.x, GameData::SCREEN_RES.y), "Pong", sf::Style::Close);
}

const void GameManager::sfEventUpdate()
{
	while (window.pollEvent(sfEvent))
	{
		if ((sfEvent.type == sf::Event::KeyPressed && sfEvent.key.code == sf::Keyboard::Escape) || (sfEvent.type == sf::Event::Closed))
			window.close();
		else if (sfEvent.type == sf::Event::KeyPressed)
		{
			states.front()->updateInput(sfEvent);
		}
	}
}

const void GameManager::deltaTimeUpdate()
{
	deltaTime = clock.restart().asSeconds();
}

const void GameManager::update()
{
	sfEventUpdate();
	states.front()->update();
}

const void GameManager::render()
{
	window.clear();
	states.front()->render();
	window.display();
}

const void GameManager::Init()
{
	while (window.isOpen())
	{
		deltaTimeUpdate();
		update();
		render();
		if (states.size() >= 2)
			states.pop_back();
	}
	return void();
}

const void GameManager::changeState(const stateNames & newState)
{
	switch (newState)
	{
	case stateNames::Menu:
		currentState = stateNames::Menu;
		states.push_front(new _Menu(window, deltaTime,_Menu::menutype::start));
		break;
	case stateNames::Game:
		currentState = stateNames::Game;
		states.push_front(new _Game(window, deltaTime));
		break;
	case stateNames::Player1Wins:
		currentState = stateNames::Player1Wins;
		states.push_front(new _Menu(window, deltaTime, _Menu::menutype::player1wins));
		break;
	case stateNames::Player2Wins:
		currentState = stateNames::Player2Wins;
		states.push_front(new _Menu(window, deltaTime, _Menu::menutype::player2wins));
		break;
	}
}

GameManager::~GameManager()
{
	states.clear();
}
