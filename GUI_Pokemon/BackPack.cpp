#include "BackPack.h"
#include <iostream>
#include "ListOfPokemon.h"
//#include "../../Pokemon/Pokemon/Trener.h"


BackPack::BackPack()
{
}

BackPack::BackPack(float width, float height, Player& player, Trener* trener)
{
	
	MenuGeneric();
	this->player = &player;

	this->w = width;
	this->h = height;

	this->trener = trener;
	
	this->tItems.loadFromFile("../Images/Batoh.png");
	this->sItems.setTexture(tItems);
	int max_items = 2;
	sItems.setPosition(sf::Vector2f((w / 3), h / (max_items + 2)));

	// initialize items
	sf::Text penize, potiony, pokebaly;
	
	penize.setFont(font);
	penize.setFillColor(sf::Color::White);
	penize.setString(std::to_string(this->trener->getPenize()));
	penize.setPosition(sf::Vector2f((w / 2), h / (max_items + 1) * 0.80));
	items.push_back(penize);
	potiony.setFont(font);
	potiony.setFillColor(sf::Color::White);
	potiony.setString(std::to_string(this->trener->getBatoh().getPotiony()));
	potiony.setPosition(sf::Vector2f((w / 2), h / (max_items + 1) * 1.1));
	items.push_back(potiony);
	pokebaly.setFont(font);
	pokebaly.setFillColor(sf::Color::White);
	pokebaly.setPosition(sf::Vector2f((w / 2), h / (max_items + 1) * 1.4));
	pokebaly.setString(std::to_string(this->trener->getBatoh().GetPokebaly()));
	items.push_back(pokebaly);

	
	
	
	// initialize menu
	for (unsigned int i = 0; i<max_items; i++)
	{
		sf::Text item;

		item.setFont(font);
		item.setFillColor(sf::Color::White);
		item.setPosition(sf::Vector2f(sf::Vector2f((w / 2), h / (max_items + 1)*(i+1.8))));

		menu.push_back(item);
	}
	menu[0].setFillColor(sf::Color::Red);
	menu[0].setString("USE POTION");
	menu[1].setString("Return");

}

BackPack::~BackPack()
{
}

void BackPack::draw(sf::RenderWindow& window)
{
	std::cout << "BAGL" << std::endl;
	



	bool endDraw = true;
	while (endDraw)
	{
		// handle events
		sf::Event event;
		while (window.pollEvent(event))
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
					switch (getPressedItem())
					{
					case 0: {
						std::cout << "Heal" << std::endl;
						//re-initialization of pokemon list
						ListOfPokemon list_of_pokemon(w, h, *player);
						list_of_pokemon.draw(window);
						break; }
					case 1:
						std::cout << "Back" << std::endl;
						endDraw = false;
						break;
					}
					break;
				}
			}
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();

		for (unsigned int i = 0; i < items.size(); i++)
		{
			window.draw(items[i]);
		}
		
		for (unsigned int i = 0; i < menu.size(); i++)
		{
			window.draw(menu[i]);
		}
		window.draw(sItems);
		window.display();
	}
}


