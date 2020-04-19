#include "Menu.h"
#include"GameManager.h"
void _Menu::fontSetup()
{
	if (!font.loadFromFile("../Fonts/Market_Deco.ttf"))
		throw("error loading font");
}

void _Menu::backgroundSetup()
{
	switch (mtype)
	{
	case start:
	if (!backgroundTex.loadFromFile("../Textures/background1.jpg"))
		throw("error finding background image");
		break;
	case player1wins:
		if (!backgroundTex.loadFromFile("../Textures/Player1wins.jpg"))
			throw("error finding background image");
		break;
	case player2wins:
		if (!backgroundTex.loadFromFile("../Textures/Player2wins.jpg"))
			throw("error finding background image");
		break;
	default:
		break;
	}
	background.setTexture(&backgroundTex);
	background.setSize(GameData::SCREEN_RES);//TODO change to suit res
	background.setPosition(0, 0);
}

void _Menu::guiSetup()
{
	for (int i(0); i < 2; i++)
	{
		menu[i].setScale(Vec2f(2, 2));
		menu[i].setFont(font);
		menu[i].setFillColor(sf::Color::White);
		menu[i].setPosition(Vec2f(GameData::SCREEN_RES.x - ((GameData::SCREEN_RES.x / 2.f)), GameData::SCREEN_RES.y / 15.f * (i + 10.f)));
	}
	if(mtype==menutype::start)
		menu[0].setString("Play");
	else
		menu[0].setString("Play again");
	menu[1].setString("Exit");
	selected = 0;
}

_Menu::_Menu(sf::RenderWindow& _window, float& _deltaTime, menutype _mtype) :
	State(_window, _deltaTime), mtype(_mtype)
{
	backgroundSetup();
	fontSetup();
	guiSetup();
	colourChange();
}

void _Menu::render()
{
	window.draw(background);
	window.draw(menu[0]);
	window.draw(menu[1]);
}

void _Menu::updateInput(sf::Event& event)
{
		if (event.key.code==(sf::Keyboard::W) || event.key.code == (sf::Keyboard::Up))
			moveUp();
		if (event.key.code == (sf::Keyboard::S) || event.key.code == (sf::Keyboard::Down))
			moveDown();
	if (event.key.code == (sf::Keyboard::Enter))
	{
		switch (selected)
		{
		case 0:
			GameManager::Instance().changeState(GameManager::stateNames::Game);
			break;
		case 1:
			window.close();
			break;
		default:
			break;
		}
	}
}

void _Menu::moveUp()
{
	if (selected - 1 >= 0)
		selected--;
	colourChange();
}

void _Menu::moveDown()
{
	if (selected + 1 < 2)
		selected++;
	colourChange();
}

void _Menu::colourChange()
{
	for (int i(0); i < 2; i++)
		if (i == selected)
			menu[i].setFillColor(sf::Color::Red);
		else
			menu[i].setFillColor(sf::Color::White);
}