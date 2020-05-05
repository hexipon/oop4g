#include "powerUp.h"
#include"Player.h"

const void powerUp::render()
{
	ship.Draw(_spritebatch);
	return void();
}

const void powerUp::update()
{
	bool _upPressed = (ship.GetPosition().y > destination.y);

	bool _downPressed = (ship.GetPosition().y < destination.y);

	bool _leftPressed = (ship.GetPosition().x > destination.x);

	bool _rightPressed = (ship.GetPosition().x < destination.x);


	if (_upPressed)
		moveUp();
	if (_downPressed)
		moveDown();
	if (_leftPressed)
		moveLeft();
	if (_rightPressed)
		moveRight();

	updateShipMovement();


	if (!(ship.GetPosition().y > 20.f && ship.GetPosition().y < (PlayArea.z+20.f)))
	{
		active = false;
	}

	return void();
}

const void powerUp::hasCollided(const int _colour)
{
	switch (colourType(_colour))
	{
	case Ship::BLUE:
	case Ship::PURPLE:
	case Ship::ORANGE:
	case Ship::YELLOW:
		health -= 0.005f;
		break;
	default:
		break;
	}
	if (health <= 0.0f)
		active = false;
	return void();
}

const void powerUp::hasCollidedWithPlayer()
{
	//power player up depending on this
	switch (colour)
	{
	case Ship::GREEN:
		Player::Get().activateShield(10.f);
		break;
	case Ship::BLUE:
		Player::Get().activateShield(5.f);
		break;
	case Ship::PURPLE:
		Player::Get().increaseHealth(75.f);
		break;
	case Ship::RED:
		Player::Get().increaseHealth(25.f);
		break;
	case Ship::ORANGE:
		Player::Get().increaseFireRate(0.05f);
		break;
	case Ship::YELLOW:
		Player::Get().increaseFireRate(0.03f);
		break;
	default:
		break;
	}
	active = false;
	return void();
}

const bool powerUp::checkCollision(const Sprite & sprite)
{
	DirectX::SimpleMath::Vector2 pos1 = DirectX::SimpleMath::Vector2(ship.GetPosition().x - (sprite.GetScreenSize().x / 2) + (ship.GetScreenSize().x / 2),
		ship.GetPosition().y + ship.GetScreenSize().y / 2);
	DirectX::SimpleMath::Vector2 pos2 = DirectX::SimpleMath::Vector2(sprite.GetPosition().x,
		sprite.GetPosition().y + sprite.GetScreenSize().y / 2);

	return(((pos1.x - pos2.x)*(pos1.x - pos2.x) + (pos1.y - pos2.y)*(pos1.y - pos2.y)) <
		(sprite.GetScreenSize().x / 2)*(sprite.GetScreenSize().x / 2) + (ship.GetScreenSize().x / 2)*(ship.GetScreenSize().x / 2));
}
