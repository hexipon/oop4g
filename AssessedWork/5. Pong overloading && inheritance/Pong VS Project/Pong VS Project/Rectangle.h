#pragma once
#include"Vec2f.h"
#include"GameObject.h"
class Rectangle : public GameObject
{
public:
	virtual void Update(const float& deltaTime) = 0;
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
	const void SetSize(const Vec2f& pos) {
		shape.setSize(pos);
	}
	const void SetColour(const sf::Color col) {
		shape.setFillColor(col);
	}
	const sf::FloatRect getGlobalBounds() {
		return shape.getGlobalBounds();
	}
private:
	sf::RectangleShape shape;
};