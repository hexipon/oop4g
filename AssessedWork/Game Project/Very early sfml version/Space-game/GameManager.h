#pragma once
#include"phf.h"
#include"State.h"
#include"Menu.h"
class GameManager
{
private:
  sf::RenderWindow *window;
  sf::Event sfEvent;
  sf::Clock clock;
  float deltaTime;
  std::deque<State*> states;
  void windowSetup();
  void varSetup();
  void startState();
  void sfEventUpdate();
  void deltaTimeUpdate();
  void update();
  void render();
public:
  GameManager();
  void start();
};

