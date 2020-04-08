#pragma once
#include"phf.h"
#include"State.h"
class CommonGameData
{
public:
  float deltaTime;
  std::deque<State*> states;
  sf::RenderWindow* window;
};

