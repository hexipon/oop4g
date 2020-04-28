#pragma once
#include"Vec2f.h"
#include"GameObject.h"
class Rectangle : public GameObject
{
public:
	virtual void Update(const float& deltaTime) = 0;
	const void Render(sf::RenderWindow& window) override {
		window.draw(shape);
	}
	const void SetOrigin(const Vec2f& off)override {
		shape.setOrigin(off);
	}
	const Vec2f GetScale() override {
		return(shape.getScale());
	}
	const Vec2f GetPos() override {
		return shape.getPosition();
	}
	const void SetPos(const Vec2f& pos) override {
		shape.setPosition(pos);
	}
	const void SetSize(const Vec2f& pos) {
		shape.setSize(pos);
	}
	const void SetColour(const sf::Color col) override {
		shape.setFillColor(col);
	}
	const sf::FloatRect getGlobalBounds() override {
		return shape.getGlobalBounds();
	}
private:
	sf::RectangleShape shape;
};