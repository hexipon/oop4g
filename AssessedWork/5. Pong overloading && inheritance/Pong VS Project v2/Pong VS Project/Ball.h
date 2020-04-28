#pragma once
#include"Vec2f.h"
#include"GameObject.h"
#include"gameData.h"
class Ball : public GameObject
{
public:
	Ball() {}
	const void Update(const float& deltaTime)  {
		if (Velocity.x != 0 || Velocity.y != 0)
		{
			Vec2f pos{ (Velocity * deltaTime) + GetPos() };
			SetPos(pos);
		}
		speedModifier += deltaTime*0.05;
	};
	void SetVel(const Vec2f& v) {
		Velocity.x = v.x*speedModifier;
		Velocity.y = v.y*speedModifier;
	}
	const Vec2f GetVel() const {
		return Vec2f{ Velocity.x,Velocity.y };
	}
	const void Render(sf::RenderWindow& window) override {
		window.draw(shape);
	}
	const void SetOrigin(const Vec2f& off) override {
		shape.setOrigin(off);
	}
	const Vec2f GetScale() {
		return(shape.getScale());
	}
	const Vec2f GetPos() override {
		return shape.getPosition();
	}
	const void SetPos(const Vec2f& pos) override {
		shape.setPosition(pos);
	}
	const void SetSize(const float& radius)  {
		shape.setRadius(radius);
	}
	const void SetColour(const sf::Color col) override {
		shape.setFillColor(col);
	}
	const sf::FloatRect getGlobalBounds() override {
		return shape.getGlobalBounds();
	}
	const void resetSpeedModifier() {
		speedModifier = 1.f;
	}
private:
	float speedModifier=1.f;
	sf::CircleShape shape;
	Vec2f Velocity;
};

