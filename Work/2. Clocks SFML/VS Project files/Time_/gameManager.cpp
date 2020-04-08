#include "gameManager.h"

gameManager::gameManager() : digClock(correctTime, sf::Vector2f(300, 0))
{
	srand((unsigned)time(NULL));
	//game setup
	winSetup();
	//Setup text
	if (!textFont.loadFromFile("Retro.ttf"))
		throw("cannot find digital clock text file");
	topText.setFont(textFont);
	bottomText.setFont(textFont);
	topText.setString("Time to play?");
	bottomText.setPosition(200, 800);
	//setup analogue clocks
	anClocks[0] = new AnClock(1, sf::Vector2f(0, 200), textFont);
	anClocks[1] = new AnClock(2, sf::Vector2f(300, 200), textFont);
	anClocks[2] = new AnClock(3, sf::Vector2f(600, 200), textFont);
	//setup digital clock
	if (!digFont.loadFromFile("digital-7.ttf"))
		throw("cannot find digital clock text file");
	digClock.init(digFont);
	setClocks();

}

void gameManager::winSetup()
{
	window.create(sf::VideoMode(1920, 1080), "What's the time?", sf::Style::Fullscreen);
}

void gameManager::sfEventUpdate()
{
	if (window.pollEvent(sfEvent))
		//while (window.pollEvent(sfEvent))
	{
		if ((sfEvent.type == sf::Event::KeyPressed && sfEvent.key.code == sf::Keyboard::Escape) || (sfEvent.type == sf::Event::Closed))
			window.close();
		if ((state == State::Playing) && (sfEvent.type == sf::Event::KeyPressed) && ((sfEvent.key.code == sf::Keyboard::Num1) || (sfEvent.key.code == sf::Keyboard::Num2) || (sfEvent.key.code == sf::Keyboard::Num3)))
			checkIfCorrect(sfEvent.key.code);
		if ((state == State::Limbo) && (sfEvent.type == sf::Event::KeyPressed) && (sfEvent.key.code == sf::Keyboard::Y))
		{
			setClocks();
			state = State::Playing;
		}
		if ((state == State::Limbo) && (sfEvent.type == sf::Event::KeyPressed) && (sfEvent.key.code == sf::Keyboard::N))
			window.close();
	}
}

void gameManager::Init()
{
	while (window.isOpen())
	{
		deltaTime = clock.restart().asSeconds();
		update();
		render();
	}

}
void gameManager::update()
{
	sfEventUpdate();
	digClock.update(deltaTime);
	for (int i = 0; i < 3; i++)
		anClocks[i]->update(deltaTime);
	//update other stuff
}

void gameManager::render()
{
	window.clear();
	//render stuff here
	digClock.render(window);
	for (int i = 0; i < 3; i++)
		anClocks[i]->render(window);
	window.draw(topText);
	window.draw(bottomText);
	window.display();
}

void gameManager::setClocks()
{
	bottomText.setString("Which clock shows the same time as the digital one? 1, 2, or 3");
	correctTime.setRandTime();
	anClocks[0]->setNewTime(correctTime);
	anClocks[1]->setNewTime();
	anClocks[2]->setNewTime();
}

void gameManager::checkIfCorrect(const int code)
{
	int clockNum=0;
	switch (code)
	{
	case 27:
		clockNum = 0;
		break;
	case 28:
		clockNum = 1;
		break;
	case 29:
		clockNum = 2;
		break;
	default:
		break;
	}
	state = State::Limbo;
	if ((anClocks[clockNum]->getTime().getHours() == correctTime.getHours()) && (anClocks[clockNum]->getTime().getMinutes() == correctTime.getMinutes()))
	{
		bottomText.setString("correct, try again? <y or n>");
	}
	else
	{
		bottomText.setString("wrong, try again?  <y or n>");
	}
}