#pragma once
#include"Vec2f.h"
#include"GameObject.h"
#include"gameData.h"
class Ball : public GameObject
{
public:
	Ball() {}
	const void Update(const float& deltaTime) {
		if (Velocity.x != 0 || Velocity.y != 0)
		{
			Vec2f pos{ (Velocity * deltaTime) + GetPos() };
			SetPos(pos);
		}
	};
	void SetVel(const Vec2f& v) {
		Velocity.x = v.x;
		Velocity.y = v.y;
	}
	const Vec2f GetVel() const {
		return Vec2f{ Velocity.x,Velocity.y };
	}
	const void Render(sf::RenderWindow& window) {
		window.draw(shape);
	}
	const void SetOrigin(const Vec2f& off) {
		shape.setOrigin(off);
	}
	const Vec2f GetScale() {
		return(shape.getScale());
	}
	const Vec2f GetPos() {
		return shape.getPosition();
	}
	const void SetPos(const Vec2f& pos) {
		shape.setPosition(pos);
	}
	const void SetSize(const float& radius) {
		shape.setRadius(radius);
	}
	const void SetColour(const sf::Color col) {
		shape.setFillColor(col);
	}
	const sf::FloatRect getGlobalBounds() {
		return shape.getGlobalBounds();
	}
private:
	sf::CircleShape shape;
	Vec2f Velocity;
};

