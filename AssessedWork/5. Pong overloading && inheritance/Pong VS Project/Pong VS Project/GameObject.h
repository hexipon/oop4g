#pragma once
#include<SFML/Graphics.hpp>
#include"Vec2f.h"
class GameObject
{
public:
	GameObject() {}
	virtual const void Render(sf::RenderWindow& window) = 0;
	virtual const void SetOrigin(const Vec2f& off) = 0;
	virtual const Vec2f GetScale() = 0;
	virtual const Vec2f GetPos() = 0;
	virtual const void SetPos(const Vec2f& pos) = 0;
	virtual const void SetColour(const sf::Color col) = 0;
	virtual const sf::FloatRect getGlobalBounds() = 0;
};

