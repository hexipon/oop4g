#include"stdafx.h"
#include "GameManager.h"



void GameManager::fontSetup()
{
	if (!font.loadFromFile("Retro.ttf")) //load font
		throw("error loading font");
}

void GameManager::windowSetup()
{
	window.create(sf::VideoMode(1920, 1080), "Sixes", sf::Style::Fullscreen);
}

void GameManager::sfEventUpdate()
{
	while (window.pollEvent(sfEvent))
	{
		switch (sfEvent.type)
		{
		case sf::Event::KeyPressed:

			switch (sfEvent.key.code)
			{
			case sf::Keyboard::Enter:
				nextScene(states.top()->getNextScene());
				break;
			case sf::Keyboard::BackSpace:
				states.top()->backspace();
				break;
			case sf::Keyboard::Escape:
				window.close();
				break;
			default:
				break;
			}
			break;
		case sf::Event::Closed:
			window.close();
		case sf::Event::TextEntered:
			states.top()->updateInput(sfEvent);
		default:
			break;
		}
	}
}

void GameManager::start()
{
	while (window.isOpen())
	{
		window.clear();
		update();
		render();
		window.display();
	}
}

void GameManager::update()
{
	sfEventUpdate();
	states.top()->update();
}

void GameManager::render()
{
		for (size_t i(lines.size()>=32 ? (lines.size()-33) : 0); i < lines.size(); i++)
		{
			window.draw(lines[i]);
		}
}

void GameManager::startState()
{
	sf::Text text;
	text.setFont(font);
	lines.push_back(text);
	states.push(new NameInput(window,lines.front(), playerName));
}

void GameManager::nextScene(const int & sceneNum)
{

	std::string numS = numInput.toAnsiString();

	switch (sceneNum)
	{
	case 1:
		numScene();
		break;
	case 2:
		if(!(numInput.getSize() < 1))
			rollDice();
		break;
	default:
		break;
	}
	sortLines();
}

void GameManager::numScene()
{
		sf::Text text;
		text.setFont(font);
		lines.push_back(text);
		states.pop();
		states.push(new NumberInput(window, lines[1], numInput));
}

void GameManager::sortLines()
{
	float ypos(0.f);
	for (size_t i(lines.size()>=33 ? (lines.size()-33) : 0); i < lines.size(); i++)
	{
		lines[i].setPosition(0.f, ypos);
		ypos += 32.f;
	}
}

void GameManager::rollDice()
{
	sf::Text text;
	text.setFont(font);
	const int goes = stoi(numInput.toAnsiString());
	Game game;
	score = game.play(goes, lines, font);
	states.pop();
	lines.push_back(text);
	states.push(new End(window, lines[lines.size()-1], playerName, score));

}

GameManager::GameManager()
{
	fontSetup();
	windowSetup();
	startState();
	start();
}