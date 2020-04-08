#pragma once
#include"phf.h"
class State
{
protected:
  sf::RenderWindow* window;
  std::deque<State*>* states;
  bool paused;
public:
  //State(sf::RenderWindow* window);
  void pauseState();
  virtual void updateInput(const float& deltaTime)=0;
  virtual void update(const float& deltaTime)=0;
  virtual void render()=0;

};

