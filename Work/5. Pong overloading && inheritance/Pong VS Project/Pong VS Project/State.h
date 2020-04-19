#pragma once
#include<SFML/Graphics.hpp>
class State
{
protected:
	sf::RenderWindow& window;
	float& deltaTime;
	State(sf::RenderWindow& _window, float& _deltaTime) : window(_window), deltaTime(_deltaTime) {}
public:
	virtual void updateInput(sf::Event& event) = 0;
	virtual void update() = 0;
	virtual void render() = 0;
};