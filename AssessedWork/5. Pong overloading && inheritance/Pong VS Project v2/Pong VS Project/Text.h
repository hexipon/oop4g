#pragma once
#include"GameObject.h"
class Text : public GameObject
{
public:
	const void Render(sf::RenderWindow& window)override {
		window.draw(text);
	}
	const void SetOrigin(const Vec2f& off)override {
		text.setOrigin(off);
	}
	const Vec2f GetScale()override {
		return(text.getScale());
	}
	const Vec2f GetPos()override {
		return text.getPosition();
	}
	const void SetPos(const Vec2f& pos)override {
		text.setPosition(pos);
	}
	const void SetSize(const float& pos) {
		text.setCharacterSize(pos);
	}
	const void SetColour(const sf::Color col)override {
		text.setFillColor(col);
	}
	const sf::FloatRect getGlobalBounds()override {
		return text.getGlobalBounds();
	}
	const void setFont(const std::string fontLocation)
	{
		if (!font.loadFromFile(fontLocation))
			throw("error loading font");
		text.setFont(font);
	}
	const void setString(std::string _text) {
		text.setString(_text);
	}
private:
	sf::Text text;
	sf::Font font;
};

