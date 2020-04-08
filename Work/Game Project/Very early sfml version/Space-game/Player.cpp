#include "phf.h"
#include "Player.h"


void Player::setupPlayer(const sf::Vector2f startPos)
{
  modeChange(0);
  ship.setTexture(shipImage);
  ship.setScale(sf::Vector2f(0.4f, 0.4f));
  ship.setPosition(sf::Vector2f(startPos.x,startPos.y-(ship.getGlobalBounds().height/2)));
}

void Player::moveUp(const float& deltaTime)
{
  if (velocity.y > -maxVelocity)
    velocity.y += acceleration * -1.f * speed*deltaTime;
}

void Player::moveDown(const float& deltaTime)
{
  if (velocity.y < maxVelocity)
    velocity.y += acceleration * 1.f * speed * deltaTime;
}

void Player::moveLeft(const float& deltaTime)
{
  if (velocity.x > -maxVelocity)
    velocity.x += acceleration * -1.f * speed * deltaTime;
}

void Player::moveRight(const float& deltaTime)
{
  if (velocity.x < maxVelocity)
    velocity.x += acceleration * 1.f * speed * deltaTime;
}

void Player::checkVelocity(const float& deltaTime)
{
  if (velocity.x > 0.f)
  {
    velocity.x -= drag * speed * deltaTime;
    if (velocity.x < 0.f)
      velocity.x = 0.f;
  }
  else if (velocity.x < 0.f)
  {
    velocity.x += drag * speed * deltaTime;
    if (velocity.x > 0.f)
      velocity.x = 0.f;
  }
  if (velocity.y > 0.f)
  {
    velocity.y -= drag * speed * deltaTime;
    if (velocity.y < 0.f)
      velocity.y = 0.f;
  }
  else if (velocity.y < 0.f)
  {
    velocity.y += drag * speed * deltaTime;
    if (velocity.y > 0.f)
      velocity.y = 0.f;
  }
}

void Player::render(sf::RenderWindow* window)
{
  window->draw(ship);
}

void Player::update(sf::Vector2u size, const float& deltaTime)
{
  checkVelocity(deltaTime);
  movePlayer(deltaTime);
  checkBorders(size);
}

void Player::checkBorders(sf::Vector2u windowSize)
{
  if (ship.getPosition().y > windowSize.y - ship.getGlobalBounds().height) //bottom boundary
  {
    ship.setPosition(ship.getPosition().x, windowSize.y - ship.getGlobalBounds().height);
    velocity.y = 0.f;
  }
  if (ship.getPosition().x > windowSize.x - ship.getGlobalBounds().width) //right boundary
  {
    ship.setPosition(windowSize.x - ship.getGlobalBounds().width, ship.getPosition().y);
    velocity.x = 0.f;
  }
  if (ship.getPosition().y <= 0) //top boundary
  {
    ship.setPosition(ship.getPosition().x, 0);
    velocity.y = 0.f;
  }
  if (ship.getPosition().x <= 0) //left boundary
  {
    ship.setPosition(0, ship.getPosition().y);
    velocity.x = 0.f;
  }
}

void Player::movePlayer(const float& deltaTime)
{
  ship.move(velocity.x * speed * deltaTime, velocity.y * speed * deltaTime);
}

void Player::modeChange(int shipNum)
{
  mode = shipNum;
  switch (shipNum)
  {
  case 0:
    if (!shipImage.loadFromFile("Textures/Player/Spaceship_01_GREEN.png"))
      throw "Could not find player spaceship image";
    break;
  case 1:
    if (!shipImage.loadFromFile("Textures/Player/Spaceship_01_ORANGE.png"))
      throw "Could not find player spaceship image";
    break;
  case 2:
    if (!shipImage.loadFromFile("Textures/Player/Spaceship_01_PURPLE.png"))
      throw "Could not find player spaceship image";
    break;
  case 3:
    if (!shipImage.loadFromFile("Textures/Player/Spaceship_01_RED.png"))
      throw "Could not find player spaceship image";
    break;
  case 4:
    if (!shipImage.loadFromFile("Textures/Player/Spaceship_01_YELLOW.png"))
      throw "Could not find player spaceship image";
    break;
  case 5:
    if (!shipImage.loadFromFile("Textures/Player/Spaceship_01_BLUE.png"))
      throw "Could not find player spaceship image";
    break;
  default:
    break;
  }

}

void Player::shoot(std::vector<Bullet>* bullets, const float& deltaTime)
{
  if (bulletTimer >= 0.3f)
  {
    bullets->push_back(Bullet(mode, sf::Vector2f(ship.getPosition().x + ship.getGlobalBounds().width, ship.getPosition().y + (ship.getGlobalBounds().height / 2)), velocity.x * speed)); //creating bullet, setting position, setting speed taking ship momentum into account
    bulletTimer = 0.f;
  }
  bulletTimer += deltaTime;
}