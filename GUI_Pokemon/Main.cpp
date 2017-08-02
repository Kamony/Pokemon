#include <SFML/Graphics.hpp>
#include <iostream>
#include "Menu.h"
#include "Game.h"
#include "BackPack.h"

using namespace sf;

int W = 1200;
int H = 800;

int main()
{
	// game window 60 fps
	RenderWindow app(VideoMode(W, H), "Pokemon!");
	app.setFramerateLimit(60);
	
	// menu play, about, exit	
	Menu mainMenu(app.getSize().x, app.getSize().y);
	// game instance
	Game game(W,H);
	
	
	while (app.isOpen())
	{
	
		// handle events
		Event event;
		while (app.pollEvent(event))
		{
			switch (event.type)
			{
			case Event::KeyPressed:
				switch (event.key.code)
				{

				case Keyboard::Up:
					mainMenu.moveUp();
					break;
				case Keyboard::Down:
					mainMenu.moveDown();
					break;
				case Keyboard::Return:
					switch (mainMenu.getPressedItem())
					{
					case 0:
						std::cout << "PLAY BUTTON" << std::endl;
						game.Play(app);
						
						break;
					case 1:
						std::cout << "ABOUT BUTTON" << std::endl;
						break;
					case 2:
						std::cout << "EXIT BUTTON" << std::endl;
						app.close();
					}
					break;
				}
				break;
			case Event::Closed:
				app.close();
			}	
		}

		app.clear();
		mainMenu.draw(app);
		app.display();
	}
	return 0;
}
