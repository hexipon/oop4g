#pragma once
#include"State.h"
#include"Player.h"
#include"Bullet.h"
#include"Enemy.h"
#include"Item.h"
class LevelOne : public State
{
private:
  std::vector<Bullet> bullets;
  std::vector<Enemy> enemies;
  std::vector<Item> items;
  Player player;
  sf::Texture backgroundTex;
  sf::RectangleShape background;
  void backgroundSetup();
  void manageEnemies();

public:
  LevelOne(sf::RenderWindow* window, std::deque<State*>* states);
  void update(const float& deltaTime);
  void render();
  void updateInput(const float& deltaTime);
};

