#pragma once
#include"phf.h"
#include"Bullet.h"
class Player
{
private:
  float bulletTimer=0.5f;
  int mode=0;
  sf::Texture shipImage;
  sf::Sprite ship;
  const float maxVelocity = 15.f;
  const float acceleration = 1.f;
  const float drag = .4f;
  float speedModifier = 1.f;
  float speed= 30 * speedModifier;
  sf::Vector2f velocity;
  void checkVelocity(const float& deltaTime);
  void movePlayer(const float& deltaTime);
  void checkBorders(sf::Vector2u size);
public:
  void setupPlayer(const sf::Vector2f startPos);
  void moveUp(const float& deltaTime);
  void moveDown(const float& deltaTime);
  void moveLeft(const float& deltaTime);
  void moveRight(const float& deltaTime);
  void render(sf::RenderWindow* window);
  void update(sf::Vector2u size, const float& deltaTime);
  void modeChange(int shipNum);
  void shoot(std::vector<Bullet>* bullets, const float& deltaTime);
};

