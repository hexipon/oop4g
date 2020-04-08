#pragma once
#include"State.h"
class Menu : public State
{
private:
  sf::Texture backgroundTex;
  sf::RectangleShape background;
  sf::Font font;
  sf::Text menu[3];
  //sf::RectangleShape buttonBackground; //TODO add button background images
  int selected;
  float timeout;
  void fontSetup();
  void backgroundSetup();
  void guiSetup();
  void moveUp();
  void moveDown();
  void colourChange();

public:
  Menu(sf::RenderWindow* window, std::deque<State*>* states);
  void update(const float& deltaTime);
  void render();
  void updateInput(const float& dt);
};

