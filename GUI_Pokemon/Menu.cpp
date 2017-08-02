#include "Menu.h"
#include <iostream>


Menu::Menu(float width, float height)
{
	MenuGeneric();
	
	if (!font.loadFromFile("../Fonts/arial.ttf"))
	{
		std::cerr << "font not loaded" << std::endl;
	}


	if (!bg_texture.loadFromFile("../Images/mainMenu.png"))
	{
		std::cerr << "texture not loaded - BackPack" << std::endl;
	}
	bg.setTexture(bg_texture);


	sf::Text item1;
	sf::Text item2;
	sf::Text item3;
	menu.push_back(item1);
	menu.push_back(item2);
	menu.push_back(item3);

	menu[0].setFont(font);
	menu[0].setFillColor(sf::Color::Red);
	menu[0].setString("Play");
	menu[0].setCharacterSize(50);
	
	
	menu[1].setFont(font);
	menu[1].setFillColor(sf::Color::Black);
	menu[1].setString("About");
	menu[1].setCharacterSize(35);
	
	
	menu[2].setFont(font);
	menu[2].setFillColor(sf::Color::Black);
	menu[2].setString("Exit");
	
	int maxItems = menu.size();
	menu[2].setPosition(sf::Vector2f(723,632));
	menu[1].setPosition(sf::Vector2f(839,217));
	menu[0].setPosition(sf::Vector2f(245,362));
	selectedItemId = 0;
}

Menu::~Menu()
{
}




void Menu::draw(sf::RenderWindow& window)
{
	window.draw(bg);
	for (unsigned int i = 0; i< menu.size(); i++)
	{
		window.draw(menu[i]);
	}
	
}

void Menu::moveUp()
{
	if (selectedItemId - 1 >= 0)
	{
		menu[selectedItemId].setFillColor(sf::Color::Black);
		selectedItemId--;
		menu[selectedItemId].setFillColor(sf::Color::Red);
	}
}

void Menu::moveDown()
{
	if (selectedItemId + 1 < menu.size())
	{
		menu[selectedItemId].setFillColor(sf::Color::Black);
		selectedItemId++;
		menu[selectedItemId].setFillColor(sf::Color::Red);
	}
}
