#include "Ship.h"

const void Ship::changeMaxVel()
{
	return void();
}

const void Ship::changeAccelleration()
{
	return void();
}

const void Ship::changeMode()
{
	return void();
}

const void Ship::moveUp()
{
	if (Velocity.y > -maxVelocity)
		Velocity.y += acceleration * -1.f * speed*deltaTime;
	return void();
}

const void Ship::moveDown()
{
	if (Velocity.y < maxVelocity)
		Velocity.y += acceleration * 1.f * speed * deltaTime;
	return void();
}

const void Ship::moveLeft()
{
	if (Velocity.x > -maxVelocity)
		Velocity.x += acceleration * -1.f * speed * deltaTime;
	return void();
}

const void Ship::moveRight()
{
	if (Velocity.x < maxVelocity)
		Velocity.x += acceleration * 1.f * speed * deltaTime;
	return void();
}

const void Ship::checkVelocity()
{
	if (Velocity.x > 0.f)
	{
		Velocity.x -= drag * speed * deltaTime;
		if (Velocity.x < 0.f)
			Velocity.x = 0.f;
	}
	else if (Velocity.x < 0.f)
	{
		Velocity.x += drag * speed * deltaTime;
		if (Velocity.x > 0.f)
			Velocity.x = 0.f;
	}
	if (Velocity.y > 0.f)
	{
		Velocity.y -= drag * speed * deltaTime;
		if (Velocity.y < 0.f)
			Velocity.y = 0.f;
	}
	else if (Velocity.y < 0.f)
	{
		Velocity.y += drag * speed * deltaTime;
		if (Velocity.y > 0.f)
			Velocity.y = 0.f;
	}
}

const void Ship::updateShipMovement()
{
	checkVelocity();
	moveShip();
	return void();
}

const void Ship::moveShip()
{
	ship.SetPosition(DirectX::SimpleMath::Vector2(ship.GetPosition().x + (Velocity.x * speed*(gameData::Get().WindowSize.x / gameData::Get().MaxWindowSize.x) * deltaTime), ship.GetPosition().y + (Velocity.y * speed *(gameData::Get().WindowSize.x / gameData::Get().MaxWindowSize.x)* deltaTime) ));
	return void();
}
