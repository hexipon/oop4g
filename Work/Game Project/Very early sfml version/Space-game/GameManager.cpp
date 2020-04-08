#include"phf.h"
#include "GameManager.h"

void GameManager::windowSetup()//TODO add graphics settings
{
  window=new sf::RenderWindow(sf::VideoMode(1920, 1080), "Space shooter", sf::Style::Fullscreen);
}

void GameManager::varSetup()
{
  window = NULL;
  deltaTime = 0.f;
}

void GameManager::startState()
{
  states.push_front(new Menu(window,&states));
}

GameManager::GameManager()
{
  windowSetup();
  startState();
  start();
}

void GameManager::start()
{
  while (window->isOpen())
  {
    deltaTimeUpdate();
      update();
      render();
      if (states.size() >= 2)
        states.pop_back();
  }
}

void GameManager::sfEventUpdate()
{
  while (window->pollEvent(sfEvent))
  {
    if ((sfEvent.type == sf::Event::KeyPressed && sfEvent.key.code == sf::Keyboard::Escape) || (sfEvent.type == sf::Event::Closed))
      window->close();
  }
}

void GameManager::deltaTimeUpdate()
{
  deltaTime = clock.restart().asSeconds();
}

void GameManager::update()
{
  sfEventUpdate();
  states.front()->update(deltaTime);
}

void GameManager::render()
{
  window->clear();
  states.front()->render();
  window->display();
}
