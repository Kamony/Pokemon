#include "Store.h"
#include <iostream>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Event.hpp>


Store::Store(Player &player)
{
	this->player = &player;
	this->obchod = Obchod();


	if (!bg_texture.loadFromFile("../Images/playerTools/Pokedex.png"))
	{
		std::cerr << "texture not loaded - STORE" << std::endl;
	}
	bg.setTexture(bg_texture);


	money.setFont(font);
	money.setString("Your money: " + std::to_string(player.getBackEndTrener()->getPenize()));
	money.setPosition(sf::Vector2f(450, 100));


	buyPokebal.setFont(font);
	buyPokebal.setString("BUY POKEBAL - 100");
	buyPokebal.setPosition(sf::Vector2f(450, 200));

	buyPotion.setFont(font);
	buyPotion.setString("BUY POTION - 50");
	buyPotion.setPosition(sf::Vector2f(450, 250));
	stav.setFont(font);
	stav.setPosition(sf::Vector2f(450, 400));
	returnButton.setFont(font);
	returnButton.setString("Return");
	returnButton.setPosition(money.getPosition() + sf::Vector2f(0, 650));
	//menu.push_back(money);
	menu.push_back(buyPokebal);
	menu.push_back(buyPotion);
	menu.push_back(returnButton);
	//menu.push_back(stav);

	menu[0].setFillColor(sf::Color::Red);
}


Store::~Store()
{
}

void Store::draw(sf::RenderWindow& app)
{
	bool returnNotPressed = true;
	sf::Clock clock;
	int moneyCurrent = 0;
	while (returnNotPressed)
	{
		
		app.clear();

		// handle events
		
		sf::Event event;
		while (app.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::KeyPressed:
				switch (event.key.code)
				{
				case sf::Keyboard::Up:
					moveUp();
					break;
				case sf::Keyboard::Down:
					moveDown();
					break;
				case sf::Keyboard::Return:
					clock.restart();
					moneyCurrent = player->getBackEndTrener()->getPenize();
					switch (getPressedItem())
					{
					case 1:
						std::cout << "Buy potion" << std::endl;
						obchod.kupPotion(*player->getBackEndTrener());
						if (moneyCurrent > 49)
						{
							stav.setString("Potion Bought");
							stav.setFillColor(sf::Color::Green);
						}
						else
						{
							stav.setString("NOT ENOUGH MONEY!");
							stav.setFillColor(sf::Color::Red);
						}
						break;
					case 0:
						std::cout << "Buy pokeball" << std::endl;
						obchod.kupPokebal(*player->getBackEndTrener());
						if (moneyCurrent > 99) 
						{
							stav.setString("Pokeball Bought");
							stav.setFillColor(sf::Color::Green);
						}
						else
						{
							stav.setString("NOT ENOUGH MONEY!");
							stav.setFillColor(sf::Color::Red);
						}
						break;
					case 2:
						std::cout << "Back" << std::endl;
						returnNotPressed = false;
						break;
					}
					moneyCurrent = player->getBackEndTrener()->getPenize();
					money.setString("Your money: " + std::to_string(moneyCurrent));
					break;
				}
				
			}
			if (event.type == sf::Event::Closed)
				app.close();
		}

		app.draw(bg);

		for (unsigned int i = 0; i < menu.size(); i++)
		{
			app.draw(menu[i]);
		}

		if (clock.getElapsedTime().asSeconds() < 3)
		{
			app.draw(stav);
		}
		app.draw(money);
		app.display();
	}

}
