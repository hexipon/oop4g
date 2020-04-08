#include"phf.h"
#include "LevelOne.h"

LevelOne::LevelOne(sf::RenderWindow* window, std::deque<State*>* states)
{
  this->states = states;
  this->window = window;
  backgroundSetup();
  player.setupPlayer(sf::Vector2f(0, (window->getSize().y / 2)));
}

void LevelOne::backgroundSetup()
{
  if (!backgroundTex.loadFromFile("Textures/background1.jpg"))
    throw("error finding background image");
  background.setTexture(&backgroundTex);
  background.setSize(sf::Vector2f(1920, 1080));//TODO change to suit res
  background.setPosition(0, 0);
}

void LevelOne::manageEnemies()
{
}

void LevelOne::update(const float& deltaTime)
{
  updateInput(deltaTime);
  for(size_t i(0);i<bullets.size();i++)
    if(bullets[i].update(deltaTime, window))
      bullets.erase(bullets.begin() + i);
  player.update(window->getSize(),deltaTime);
}

void LevelOne::render()
{
  window->draw(background);
  for (auto i : bullets)
    i.render(window);
  player.render(window);
}

void LevelOne::updateInput(const float& deltaTime)
{
  //move player ship
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    player.moveUp(deltaTime);
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    player.moveLeft(deltaTime);
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    player.moveDown(deltaTime);
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    player.moveRight(deltaTime);
  //change player ship mode
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::T))
    player.modeChange(0);
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Y))
    player.modeChange(1);
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::U))
    player.modeChange(2);
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::I))
    player.modeChange(3);
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::O))
    player.modeChange(4);
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::P))
    player.modeChange(5);
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
    player.shoot(&bullets,deltaTime);
}
