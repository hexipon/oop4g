#pragma once

#include<SFML/Graphics.hpp>
#include"Vec2f.h"
class Application;
/*
Cannon, walls and ball are all GameObjs
Here we've hidden how we are storing position and make it appear to
be a Vec2f (our type), when in fact it's a sf::Vector2f inside the sprite
We've hidden the use of the sprite.
Now - you might say, you didn't need to bother, perhaps so, but it demonstrates
the technique and means this code could be changed to a different sprite/pos system
easily.
*/
class GameObj
{
public:
	GameObj() : Vel{ 0, 0 } {};
	void Update();
	void Render(sf::RenderWindow& window) {
		window.draw(Sprite);
	}
	void SetTexture(const sf::Texture& t) {
		Sprite.setTexture(t, true);
	}
	void SetTexture(const sf::Texture& t, const sf::IntRect& rect) {
		Sprite.setTexture(t);
		Sprite.setTextureRect(rect);
	}
	void SetOrigin(const Vec2f& off) {
		Sprite.setOrigin(sf::Vector2f(off.x, off.y));
	}
	void SetScale(const Vec2f& s) {
		Sprite.setScale(s.x, s.y);
	}
	Vec2f GetScale() {
		return Vec2f{ Sprite.getScale().x, Sprite.getScale().y };
	}
	Vec2f GetPos() {
		return Vec2f{ Sprite.getPosition().x,Sprite.getPosition().y };
	}
	void SetPos(const Vec2f& pos) {
		Sprite.setPosition(pos.x, pos.y);
	}
	float GetDegrees() {
		return Sprite.getRotation();
	}
	void SetDegrees(float angle) {
		Sprite.setRotation(angle);
	}
	void AddRotation(float angle) {
		Sprite.rotate(angle);
	}
	void SetVel(const Vec2f& v) {
		Vel.x = v.x;
		Vel.y = v.y;
	}
	sf::FloatRect getGlobalBounds() {
		return Sprite.getGlobalBounds();
	}
	const Vec2f GetVel() const {
		return Vec2f{ Vel.x,Vel.y };
	}
	Vec2f GetDim() const {
		return Vec2f{ (float)Sprite.getTextureRect().width, (float)Sprite.getTextureRect().height };
	}

private:
	sf::Sprite Sprite; //image and position
	Vec2f Vel;	//velocity
};