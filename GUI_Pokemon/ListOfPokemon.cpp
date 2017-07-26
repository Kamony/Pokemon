#include "ListOfPokemon.h"
#include <iostream>



ListOfPokemon::ListOfPokemon(float w, float h, std::vector<GraphicPokemon>& list, Trener* trener):list(list)
{
	this->trener = trener;
	this->sum = list.size();

	for (unsigned int i = 0; i<sum; i++)
	{
		sf::Text item;

		item.setFont(font);
		item.setFillColor(sf::Color::White);
		item.setPosition(sf::Vector2f(w / 5, h / (sum + 1) * i / 10));
		this->list[i].setPosition(item.getPosition() + sf::Vector2f(-10, 0));
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
		for (unsigned int i = 0; i < sum+1; i++)
		{
			window.draw(menu[i]);
			window.draw(list[i]);
		}
		
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

