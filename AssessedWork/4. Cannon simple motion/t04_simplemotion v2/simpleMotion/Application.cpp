#include "Application.h"

sf::Time Application::sElapsedSecs;	//as it's static it need instantiating separately

Application::Application()
{
	// Create the main window
	Window.create(sf::VideoMode(GDC::SCREEN_RES.x, GDC::SCREEN_RES.y), "Simple motion");
	Game.Initialise(Window);
}

void Application::Run()
{
	// Start the game loop 
	sf::Clock clock;
	while (Window.isOpen())
	{
		// Process events
		sf::Event event;
		while (Window.pollEvent(event))
		{
			// Close window: exit
			if (event.type == sf::Event::Closed)
				Window.close();
			if (event.type == sf::Event::TextEntered)
			{
				if (event.text.unicode < GDC::ASCII_RANGE)
					Game.TextEntered(static_cast<char>(event.text.unicode));
			}
		}

		sElapsedSecs = clock.restart();

		// Clear screen
		Window.clear();

		Game.Update();
		Game.Render();

		// Update the window
		Window.display();
	}
}
