#pragma once
//dimensions in 2D that are floating point numbers
struct Vec2f
{
	float x, y;
	const Vec2f() { x = 0; y = 0; }
	const Vec2f(const sf::Vector2f xy) : x(xy.x), y(xy.y) {}
	const Vec2f(const float x2, const float y2) : x(x2), y(y2) {}
	operator sf::Vector2f() const { return sf::Vector2f(x, y); }
	const bool operator ==(const sf::Vector2f& vector2f) const { return ((x == vector2f.x) && (y == vector2f.y)); }
	const bool operator !=(const sf::Vector2f& vector2f) const { return !((x == vector2f.x) && (y == vector2f.y)); }
	const bool operator ==(const Vec2f& _vec2f) const { return ((x == _vec2f.x) && (y == _vec2f.y)); }
	const bool operator !=(const Vec2f& _vec2f) const { return !((x == _vec2f.x) && (y == _vec2f.y)); }
	const Vec2f operator *(const float& _float) const { return Vec2f(x*_float, y*_float); }
	const Vec2f operator +=(const Vec2f& _Vec2f) const { return Vec2f(x + _Vec2f.x, y + _Vec2f.y); }
	const Vec2f operator +=(const sf::Vector2f& vector2f) const { return Vec2f(x + vector2f.x, y + vector2f.y); }
	const Vec2f operator +(const sf::Vector2f& vector2f) const { return Vec2f(x + vector2f.x, y + vector2f.y); }
	const Vec2f operator +(const Vec2f& _Vec2f) const { return Vec2f(x + _Vec2f.x, y + _Vec2f.y); }
};