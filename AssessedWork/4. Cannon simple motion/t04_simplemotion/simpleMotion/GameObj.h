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
	GameObj() : mVel{ 0, 0 } {};
	void Update();
	void Render(sf::RenderWindow& window) {
		window.draw(mSprite);
	}
	void SetTexture(const sf::Texture& t) {
		mSprite.setTexture(t, true);
	}
	void SetTexture(const sf::Texture& t, const sf::IntRect& rect) {
		mSprite.setTexture(t);
		mSprite.setTextureRect(rect);
	}
	void SetOrigin(const Vec2f& off) {
		mSprite.setOrigin(sf::Vector2f(off.x, off.y));
	}
	void SetScale(const Vec2f& s) {
		mSprite.setScale(s.x, s.y);
	}
	Vec2f GetScale() {
		return Vec2f{ mSprite.getScale().x, mSprite.getScale().y };
	}
	Vec2f GetPos() {
		return Vec2f{ mSprite.getPosition().x,mSprite.getPosition().y };
	}
	void SetPos(const Vec2f& pos) {
		mSprite.setPosition(pos.x, pos.y);
	}
	float GetDegrees() {
		return mSprite.getRotation();
	}
	void SetDegrees(float angle) {
		mSprite.setRotation(angle);
	}
	void AddRotation(float angle) {
		mSprite.rotate(angle);
	}
	void SetVel(const Vec2f& v) {
		mVel.x = v.x;
		mVel.y = v.y;
	}
	sf::FloatRect getGlobalBounds() {
		return mSprite.getGlobalBounds();
	}
	const Vec2f GetVel() const {
		return Vec2f{ mVel.x,mVel.y };
	}
	Vec2f GetDim() const {
		return Vec2f{ (float)mSprite.getTextureRect().width, (float)mSprite.getTextureRect().height };
	}

private:
	sf::Sprite mSprite; //image and position
	Vec2f mVel;	//velocity
};