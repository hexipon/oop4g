#include "Blockade.h"

const void Blockade::render()
{
	ship.Draw(_spritebatch);
	return void();
}

const void Blockade::update()
{
	if (ship.GetPosition().y > PlayArea.z)
		setDestination(DirectX::SimpleMath::Vector2(ship.GetPosition().x, PlayArea.x));
	if (ship.GetPosition().y < PlayArea.x)
		setDestination(DirectX::SimpleMath::Vector2(ship.GetPosition().x, PlayArea.z));

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

	return void();
}

const void Blockade::hasCollided(const int _colour)
{
	switch (colour)
	{
	case Ship::GREEN:
		switch (colourType(_colour))
		{
		case Ship::BLUE:
			health -= 0.5f;
			break;
		case Ship::PURPLE:
			health -= 2.5f;
			break;
		case Ship::RED:
			health -= 5.f;
			break;
		case Ship::ORANGE:
			health -= 2.5f;
			break;
		case Ship::YELLOW:
			health -= 0.5f;
			break;
		default:
			break;
		}
		break;
	case Ship::BLUE:
		switch (colourType(_colour))
		{
		case Ship::GREEN:
			health -= 0.5f;
			break;
		case Ship::PURPLE:
			health -= 0.5f;
			break;
		case Ship::RED:
			health -= 2.5f;
			break;
		case Ship::ORANGE:
			health -= 5.f;
			break;
		case Ship::YELLOW:
			health -= 2.5f;
			break;
		default:
			break;
		}
		break;
	case Ship::PURPLE:
		switch (colourType(_colour))
		{
		case Ship::GREEN:
			health -= 2.5f;
			break;
		case Ship::BLUE:
			health -= 0.5f;
			break;
		case Ship::RED:
			health -= 0.5f;
			break;
		case Ship::ORANGE:
			health -= 2.5f;
			break;
		case Ship::YELLOW:
			health -= 5.f;
			break;
		default:
			break;
		}
		break;
	case Ship::RED:
		switch (colourType(_colour))
		{
		case Ship::GREEN:
			health -= 5.f;
			break;
		case Ship::BLUE:
			health -= 2.5f;
			break;
		case Ship::PURPLE:
			health -= 0.5f;
			break;
		case Ship::ORANGE:
			health -= 0.5f;
			break;
		case Ship::YELLOW:
			health -= 2.5f;
			break;
		default:
			break;
		}
		break;
	case Ship::ORANGE:
		switch (colourType(_colour))
		{
		case Ship::GREEN:
			health -= 2.5f;
			break;
		case Ship::BLUE:
			health -= 5.f;
			break;
		case Ship::PURPLE:
			health -= 2.5f;
			break;
		case Ship::RED:
			health -= 0.5f;
			break;
		case Ship::YELLOW:
			health -= 0.5f;
			break;
		default:
			break;
		}
		break;
	case Ship::YELLOW:
		switch (colourType(_colour))
		{
		case Ship::GREEN:
			health -= 0.5f;
			break;
		case Ship::BLUE:
			health -= 2.5f;
			break;
		case Ship::PURPLE:
			health -= 5.f;
			break;
		case Ship::RED:
			health -= 2.5f;
			break;
		case Ship::ORANGE:
			health -= 0.5f;
			break;
		default:
			break;
		}
		break;
	default:
		break;
	}

	if (health <= 0.0f)
		active = false;
	return void();
}

const bool Blockade::checkCollision(const Sprite & sprite)
{
	DirectX::SimpleMath::Vector2 pos1 = DirectX::SimpleMath::Vector2(ship.GetPosition().x - (sprite.GetScreenSize().x / 2) + (ship.GetScreenSize().x / 2),
		ship.GetPosition().y + ship.GetScreenSize().y / 2);
	DirectX::SimpleMath::Vector2 pos2 = DirectX::SimpleMath::Vector2(sprite.GetPosition().x,
		sprite.GetPosition().y + sprite.GetScreenSize().y / 2);

	return(((pos1.x - pos2.x)*(pos1.x - pos2.x) + (pos1.y - pos2.y)*(pos1.y - pos2.y)) <
		(sprite.GetScreenSize().x / 2)*(sprite.GetScreenSize().x / 2) + (ship.GetScreenSize().x / 2)*(ship.GetScreenSize().x / 2));
}
