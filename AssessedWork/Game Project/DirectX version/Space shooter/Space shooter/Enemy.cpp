#include "Enemy.h"
#include"Player.h"

const void Enemy::shoot()
{
	Bullet mis(_d3d, _spritebatch, deltaTime, "EnemyBullets", -1);
	bullets.push_back(mis);
	DirectX::SimpleMath::Vector2 bulletpos(ship.GetPosition().x, ship.GetPosition().y + (ship.GetScreenSize().y / 2) + guns1Distance * (gameData::Get().WindowSize.x / gameData::Get().MaxWindowSize.x));
	bullets.back().Init(bulletpos, colour, Velocity.x*speed*(gameData::Get().WindowSize.x / gameData::Get().MaxWindowSize.x));
	missileTimer = GetClock() + missile_debounce;
	Bullet mis2(_d3d, _spritebatch, deltaTime, "EnemyBullets", -1);
	bullets.push_back(mis2);
	bulletpos = DirectX::SimpleMath::Vector2(ship.GetPosition().x, ship.GetPosition().y + (ship.GetScreenSize().y / 2) - guns1Distance * (gameData::Get().WindowSize.x / gameData::Get().MaxWindowSize.x));
	bullets.back().Init(bulletpos, colour, Velocity.x*speed*(gameData::Get().WindowSize.x / gameData::Get().MaxWindowSize.x));
	missileTimer = GetClock() + missile_debounce;
	return void();
}

const void Enemy::render()
{
	ship.Draw(_spritebatch);
	return void();
}

const void Enemy::update()
{
	destination.y = Player::Get().getPosition().y + Player::Get().GetScreenSize().y / 2 - ship.GetScreenSize().y / 2;

	bool _upPressed = (ship.GetPosition().y > destination.y);

	bool _downPressed = (ship.GetPosition().y < destination.y);

	bool _leftPressed = (ship.GetPosition().x > destination.x);

	bool _rightPressed = (ship.GetPosition().x < destination.x);

	bool _spacePressed = (GetClock() > missileTimer);

	if (_upPressed)
		moveUp();
	if (_downPressed)
		moveDown();
	if (_leftPressed)
		moveLeft();
	if (_rightPressed)
		moveRight();
	if (_spacePressed)
		shoot();

	updateShipMovement();
	return void();
}

const void Enemy::hasCollided(const int _colour)
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
	if (health <= 0)
		active = false;
	return void();
}

const bool Enemy::checkCollision(const Sprite & sprite)
{
	DirectX::SimpleMath::Vector2 pos1 = DirectX::SimpleMath::Vector2(ship.GetPosition().x - (sprite.GetScreenSize().x / 2) + (ship.GetScreenSize().x / 2),
		ship.GetPosition().y + ship.GetScreenSize().y / 2);
	DirectX::SimpleMath::Vector2 pos2 = DirectX::SimpleMath::Vector2(sprite.GetPosition().x,
		sprite.GetPosition().y + sprite.GetScreenSize().y / 2);

	return(((pos1.x - pos2.x)*(pos1.x - pos2.x) + (pos1.y - pos2.y)*(pos1.y - pos2.y)) <
		(sprite.GetScreenSize().x / 2)*(sprite.GetScreenSize().x / 2) + (ship.GetScreenSize().x / 2)*(ship.GetScreenSize().x / 2));
}