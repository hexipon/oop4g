#include "Player.h"
#include"Manager.h"



const void Player::render()
{
	ship.Draw(_spritebatch);
	if(shield.isActive())
		shield.render();
	return void();
}

const void Player::update()
{
	const bool _upPressed =
		Manager::mouseAndKeyInput.IsPressed(VK_W) || Manager::mouseAndKeyInput.IsPressed(VK_UP) ||
		Manager::GamepadInput.IsPressed(0, XINPUT_GAMEPAD_DPAD_UP) || (Manager::GamepadInput.GetState(0).leftStickY > 0);

	const bool _downPressed =
		Manager::mouseAndKeyInput.IsPressed(VK_S) || Manager::mouseAndKeyInput.IsPressed(VK_DOWN) ||
		Manager::GamepadInput.IsPressed(0, XINPUT_GAMEPAD_DPAD_DOWN) || (Manager::GamepadInput.GetState(0).leftStickY < 0);

	const bool _LeftPressed =
		Manager::mouseAndKeyInput.IsPressed(VK_A) || Manager::mouseAndKeyInput.IsPressed(VK_LEFT) ||
		Manager::GamepadInput.IsPressed(0, XINPUT_GAMEPAD_DPAD_LEFT) || (Manager::GamepadInput.GetState(0).leftStickX < 0);

	const bool _RightPressed =
		Manager::mouseAndKeyInput.IsPressed(VK_D) || Manager::mouseAndKeyInput.IsPressed(VK_RIGHT) ||
		Manager::GamepadInput.IsPressed(0, XINPUT_GAMEPAD_DPAD_RIGHT) || (Manager::GamepadInput.GetState(0).leftStickX > 0);

	const bool _spacePressed =
		Manager::GamepadInput.IsPressed(0, XINPUT_GAMEPAD_B) ||
		Manager::mouseAndKeyInput.IsPressed(VK_SPACE);

	const bool _leftTrigger =
		Manager::GamepadInput.IsPressed(0, XINPUT_GAMEPAD_LEFT_SHOULDER) ||
		Manager::mouseAndKeyInput.IsPressed(VK_Q);
	const bool _rightTrigger =
		Manager::GamepadInput.IsPressed(0, XINPUT_GAMEPAD_RIGHT_SHOULDER) ||
		Manager::mouseAndKeyInput.IsPressed(VK_E);

	if (modeChangeCooldownTimer >= modeChangeCooldown)
	{
		if (_leftTrigger)
			colourChangeLeft();
		if (_rightTrigger)
			colourChangeRight();
		modeChangeCooldownTimer = 0.f;
	}
	if (_upPressed)
		moveUp();
	if (_downPressed)
		moveDown();
	if (_LeftPressed)
		moveLeft();
	if (_RightPressed)
		moveRight();
	if (_spacePressed)
		shoot();

	updateShipMovement();
	checkBorders();
	modeChangeCooldownTimer += deltaTime;

	if (shield.isActive())
		shield.update(DirectX::SimpleMath::Vector2(ship.GetPosition().x-(20 * (gameData::Get().WindowSize.x / gameData::Get().MaxWindowSize.x)), ship.GetPosition().y));

	return void();
}

const void Player::hasCollided(const int _colour)
{

	if (!shield.isActive() && (colourType(_colour) != colour))
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
	}

	if (health <= 0)
		Manager::Get().changeState(Manager::gameStates::EndGame);

	return void();
}

const bool Player::checkCollision(const Sprite & sprite)
{
	const float radius = shield.getRadius();
	DirectX::SimpleMath::Vector2 pos1 = DirectX::SimpleMath::Vector2(ship.GetPosition().x - (20 * (gameData::Get().WindowSize.x / gameData::Get().MaxWindowSize.x)) - (sprite.GetScreenSize().x / 2) + (ship.GetScreenSize().x / 2),
		ship.GetPosition().y + ship.GetScreenSize().y / 2);
	DirectX::SimpleMath::Vector2 pos2 = DirectX::SimpleMath::Vector2(sprite.GetPosition().x,
		sprite.GetPosition().y + sprite.GetScreenSize().y / 2);

	return(((pos1.x - pos2.x)*(pos1.x - pos2.x) + (pos1.y - pos2.y)*(pos1.y - pos2.y)) <
		(sprite.GetScreenSize().x / 2)*(sprite.GetScreenSize().x / 2) + radius * radius);
}

const void Player::checkBorders()
{
	if (ship.GetPosition().y > gameData::Get().WindowSize.y - ship.GetScreenSize().y) //bottom boundary
	{
		ship.SetPosition(DirectX::SimpleMath::Vector2(ship.GetPosition().x, gameData::Get().WindowSize.y - ship.GetScreenSize().y));
		Velocity.y = 0.f;
	}
	if (ship.GetPosition().x > gameData::Get().WindowSize.x - ship.GetScreenSize().x) //right boundary
	{
		ship.SetPosition(DirectX::SimpleMath::Vector2(gameData::Get().WindowSize.x - ship.GetScreenSize().x, ship.GetPosition().y));
		Velocity.x = 0.f;
	}
	if (ship.GetPosition().y <= 0) //top boundary
	{
		ship.SetPosition(DirectX::SimpleMath::Vector2(ship.GetPosition().x, 0));
		Velocity.y = 0.f;
	}
	if (ship.GetPosition().x <= 0) //left boundary
	{
		ship.SetPosition(DirectX::SimpleMath::Vector2(0, ship.GetPosition().y));
		Velocity.x = 0.f;
	}
	return void();
}

const void Player::colourChangeLeft()
{
	switch (colour)
	{
	case Ship::GREEN:
		colour = YELLOW;
		break;
	case Ship::BLUE:
		colour = GREEN;
		break;
	case Ship::PURPLE:
		colour = BLUE;
		break;
	case Ship::RED:
		colour = PURPLE;
		break;
	case Ship::ORANGE:
		colour = RED;
		break;
	case Ship::YELLOW:
		colour = ORANGE;
		break;
	default:
		break;
	}
	ship.SetTex(*_d3d.GetCache().Get(textures[colour]).pTex);
	return void();
}

const void Player::colourChangeRight()
{
	switch (colour)
	{
	case Ship::GREEN:
		colour = BLUE;
		break;
	case Ship::BLUE:
		colour = PURPLE;
		break;
	case Ship::PURPLE:
		colour = RED;
		break;
	case Ship::RED:
		colour = ORANGE;
		break;
	case Ship::ORANGE:
		colour = YELLOW;
		break;
	case Ship::YELLOW:
		colour = GREEN;
		break;
	default:
		break;
	}
	ship.SetTex(*_d3d.GetCache().Get(textures[colour]).pTex);
	return void();
}

const void Player::shoot()
{
	if (GetClock() > missileTimer)
	{
		Bullet mis(_d3d, _spritebatch, deltaTime, "PlayerBullets", 1);
		bullets.push_back(mis);

		DirectX::SimpleMath::Vector2 bulletpos(ship.GetPosition().x + ship.GetScreenSize().x, ship.GetPosition().y + (ship.GetScreenSize().y / 2));

		bullets.back().Init(bulletpos, colour, Velocity.x*speed*(gameData::Get().WindowSize.x/gameData::Get().MaxWindowSize.x));
		missileTimer = GetClock() + missile_debounce;
	}
	return void();
}
