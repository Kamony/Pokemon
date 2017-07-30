#include "ListOfPokemon.h"
#include <iostream>



ListOfPokemon::ListOfPokemon(float w, float h, Player &player)
{
	this->trener = player.getBackEndTrener();
	this->sum = player.getGraphicPokemonList().size();
	this->list = player.getGraphicPokemonList();
	std::string nameOfPok;
	for (unsigned int i = 0; i<sum; i++)
	{
		sf::Text item;

		item.setFont(font);
		item.setFillColor(sf::Color::White);
		item.setPosition(sf::Vector2f(w / 4.5, h / (sum + 1) * i / 8));
		this->list[i].setPosition(item.getPosition() + sf::Vector2f(-50, 0));
		
		nameOfPok = list[i].getPokemon().getJmeno();
		if (  nameOfPok == "Bulbasaur" || nameOfPok == "Charmander" || nameOfPok == "Squirtle")
		{
			this->list[i].setTextureRect(sf::IntRect(61, 105, 70, 65));
			this->list[i].setScale(0.6,0.6);
		}
		else
		{
			this->list[i].setTextureRect(sf::IntRect(0, 0, 32, 32));
			this->list[i].setScale(1.5, 1.5);
		}
		
		item.setString(list[i].getPokemon().getInfo());

		menu.push_back(item);
	}
	menu[0].setFillColor(sf::Color::Red);
	sf::Text returnItem;
	returnItem.setFont(font);
	returnItem.setFillColor(sf::Color::White);
	returnItem.setPosition(sf::Vector2f(w / 2, h / 1.1));
	returnItem.setString("RETURN");
	menu.push_back(returnItem);
}

ListOfPokemon::~ListOfPokemon()
{
}


void ListOfPokemon::draw(sf::RenderWindow& window)
{
	std::cout << "List Pokemonu" << std::endl;
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
				{
					if(static_cast<int>(getPressedItem()) >= sum)
					{
						std::cout << "RETURN" << std::endl;
						endDraw = false;
						break;
					}
					if (trener->VylecPokemona(trener->getBatoh().pokemoni[getPressedItem()]))
					{
						std::cout << trener->getBatoh().pokemoni[getPressedItem()].getJmeno() << "Vylecen!" << std::endl;
					}
					else { std::cout << trener->getBatoh().pokemoni[getPressedItem()].getJmeno() << "NEVYLECEN!" << std::endl; }
					endDraw = false;
				}
					break;
				}
			}
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();
		for (unsigned int i = 0; i < sum; i++)
		{
			window.draw(menu[i]);
			window.draw(list[i]);
		}
		window.draw(menu.back());
		window.display();
	}
}

int ListOfPokemon::drawForBattle(sf::RenderWindow& window)
{
	std::cout << "List Pokemonu" << std::endl;
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
				{
					if (static_cast<int>(getPressedItem()) >= sum)
					{
						std::cout << "RETURN" << std::endl;
						endDraw = false;
						return -1;
					}
					return getPressedItem();
				}
				}
			}
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();
		for (unsigned int i = 0; i < sum; i++)
		{
			window.draw(menu[i]);
			window.draw(list[i]);
		}
		window.draw(menu.back());

		window.display();
	}

}

