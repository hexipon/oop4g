#include "phf.h"
#include "Bullet.h"

Bullet::Bullet(const int& num, const sf::Vector2f& startPos, const float& speed)
{
  mode = num;
  this->speed = speed;
  bullet.setScale(10,10);
  bullet.setRadius(0.5f);
  bullet.setPosition(sf::Vector2f(startPos.x,startPos.y-(bullet.getGlobalBounds().height/2)));
  switch (mode)
  {
  case 0:
    bullet.setFillColor(sf::Color(0,128,0));
    break;
  case 1:
    bullet.setFillColor(sf::Color(255, 69, 0));
    break;
  case 2:
    bullet.setFillColor(sf::Color(70, 39, 89));
    break;
  case 3:
    bullet.setFillColor(sf::Color(255, 0, 0));
    break;
  case 4:
    bullet.setFillColor(sf::Color(255, 255, 0));
    break;
  case 5:
    bullet.setFillColor(sf::Color(0, 255, 255));
    break;
  default:
    break;
  }

}

bool Bullet::update(const float& deltaTime, const sf::RenderWindow* window)
{
  bullet.move((deltaTime * 600) + ((speed * deltaTime) / 2), 0);
  return((bullet.getPosition().x > window->getSize().x) || (bullet.getPosition().x <0));
}

void Bullet::render(sf::RenderWindow* window)
{
  window->draw(bullet);
}


