#include"stdafx.h"

int main() {
	sf::RenderWindow window(sf::VideoMode(1920, 1080), "SFML Template", sf::Style::Fullscreen);
	sf::Event sfEvent;

	while (window.isOpen())
	{
		while (window.pollEvent(sfEvent))
		{
			if ((sfEvent.type == sf::Event::KeyPressed && sfEvent.key.code == sf::Keyboard::Escape)
				|| (sfEvent.type == sf::Event::Closed))
				window.close();
		}
	}
	return(0);
}