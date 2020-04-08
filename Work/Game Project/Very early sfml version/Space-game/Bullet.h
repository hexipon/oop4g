#pragma once
class Bullet
{
private:
  int mode;
  sf::CircleShape bullet;
  float speed;
public:
  Bullet(const int& num, const sf::Vector2f& startPos, const float& speed);
  bool update(const float& deltaTime, const sf::RenderWindow* window);
  void render(sf::RenderWindow* window);
};

