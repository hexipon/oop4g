#include "Application.h"

sf::Time Application::sElapsedSecs;	//as it's static it need instantiating separately

Application::Application()
{
	// Create the main window
	mWindow.create(sf::VideoMode(GDC::SCREEN_RES.x, GDC::SCREEN_RES.y), "My first code");
	mGame.Initialise(mWindow);
}

void Application::Run()
{
	// Start the game loop 
	sf::Clock clock;
	while (mWindow.isOpen())
	{
		// Process events
		sf::Event event;
		while (mWindow.pollEvent(event))
		{
			// Close window: exit
			if (event.type == sf::Event::Closed)
				mWindow.close();
			if (event.type == sf::Event::TextEntered)
			{
				if (event.text.unicode < GDC::ASCII_RANGE)
					mGame.TextEntered(static_cast<char>(event.text.unicode));
			}
		}

		sElapsedSecs = clock.restart();

		// Clear screen
		mWindow.clear();

		mGame.Update();
		mGame.Render();

		// Update the window
		mWindow.display();
	}
}
