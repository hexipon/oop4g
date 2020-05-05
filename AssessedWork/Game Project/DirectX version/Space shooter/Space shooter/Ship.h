#pragma once
#include"Bullet.h"
#include"d3d.h"
#include"SpriteBatch.h"
#include"Sprite.h"
#include"gameData.h"
class Ship
{
protected:
	float health;
	d3d& _d3d;
	Sprite ship;
	DirectX::SpriteBatch& _spritebatch;
	float& deltaTime;
	const enum colourType {GREEN, BLUE,PURPLE,  RED,ORANGE, YELLOW};
	colourType colour = colourType::GREEN;
	float bulletTimer;
	const float maxVelocity = 7.f;
	const float acceleration = .2f;
	const float drag = .1f;
	float speed = 75.f;
	DirectX::SimpleMath::Vector2 Velocity;
	std::vector<Bullet> bullets;
	DirectX::SimpleMath::Vector2 destination;
	const void moveUp();
	const void moveDown();
	const void moveLeft();
	const void moveRight();
	const void checkVelocity();
	const void updateShipMovement();
	const void moveShip();
public:
	Ship(d3d& d3d_, DirectX::SpriteBatch& spritebatch_, float& deltaTime_) : _d3d(d3d_),
		_spritebatch(spritebatch_), deltaTime(deltaTime_), ship(_d3d)
	{
		active = true;
	}
	bool active = false;
	const void changeMaxVel();
	const void changeAccelleration();
	virtual const void update() =0;
	virtual const void render() =0;
	virtual const bool checkCollision(const Sprite & sprite) =0;
	virtual const void hasCollided(const int _colour) = 0;
	virtual const void init() = 0;
	const void changeMode();
	const colourType GetColour() {
		return colour;
	}
	const float getHealth() {
		return health;
	}
	void setPostion(const DirectX::SimpleMath::Vector2& pos)
	{
		ship.SetPosition(pos);
	}
	void setDestination(const DirectX::SimpleMath::Vector2& _destination) {
		destination = _destination;
	}

	const Sprite& GetSprite() {
		return ship;
	}
};

