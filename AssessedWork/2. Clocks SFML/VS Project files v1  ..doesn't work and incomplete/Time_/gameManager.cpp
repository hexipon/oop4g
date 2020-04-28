#include<stack>
#include<SFML/Graphics.hpp>
#include"ClockTime.h"
#include"DigClock.h"
#include"AnClock.h"
#include<ctime>
#include<random>
#include <assert.h>
#include "gameManager.h"


void gameManager::winSetup()
{
	window.create(sf::VideoMode(1920, 1080), "What's the time?", sf::Style::Fullscreen);
}

void gameManager::sfEventUpdate()
{
	if(window.pollEvent(sfEvent))
	//while (window.pollEvent(sfEvent))
	{
		if ((sfEvent.type == sf::Event::KeyPressed && sfEvent.key.code == sf::Keyboard::Escape) || (sfEvent.type == sf::Event::Closed))
			window.close();
	}
}

void gameManager::deltaTimeUpdate()
{

	//deltaTime = clock.getElapsedTime().asSeconds();
	//clock.restart();
	assert(deltaTime > 0);
	//deltaTime = 1.f / 60;
}

void gameManager::update()
{
	sfEventUpdate();
	correctTime.updateTime(deltaTime);
	digClock.update();
	//update other stuff
}

void gameManager::render()
{
	window.clear();
	//render stuff here
	digClock.render(window);
	window.draw(topText);
	window.draw(bottomText);
	window.display();
}

gameManager::gameManager() : digClock(correctTime, sf::Vector2f(1,1))
{
	//make all numbers actually be random
	//srand((unsigned)(time(NULL)));
	//game setup
	winSetup();
	//Setup text
	if (!textFont.loadFromFile("Retro.ttf"))
		throw("cannot find digital clock text file");
	topText.setFont(textFont);
	bottomText.setFont(textFont);
	topText.setString("Time to play?");
	bottomText.setString("Which clock shows the same time as the digital one? 1, 2, or 3");
	bottomText.setPosition(0, 1000);
	//setting initial correct time
	correctTime.setTime(randTime());
	//setup digital clock
	//digClock = new DigClock(correctTime, sf::Vector2f(1,1));
	if (!digFont.loadFromFile("digital-7.ttf"))
		throw("cannot find digital clock text file");
	digClock.init(digFont);
	//setup analogue clocks
	sf::Clock clock;
	//game loop
	while (window.isOpen())
	{
		//deltaTimeUpdate();
		deltaTime = clock.getElapsedTime().asSeconds();
		update();
		render();
		clock.restart();
	}
}

int gameManager::randTime() const
{
	std::mt19937 rng(std::time(NULL));
	//rng.seed(std::random_device()());
	std::uniform_int_distribution<int> range(0, 86400);
	return range(rng);//random time in seconds
}
