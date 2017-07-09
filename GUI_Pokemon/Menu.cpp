#include "Menu.h"


Menu::Menu(float width, float height)
{
	MenuGeneric();
	
	if (!font.loadFromFile("../Fonts/arial.ttf"))
	{
		//error
	}

	sf::Text item1;
	sf::Text item2;
	sf::Text item3;
	menu.push_back(item1);
	menu.push_back(item2);
	menu.push_back(item3);

	menu[0].setFont(font);
	menu[0].setFillColor(sf::Color::Red);
	menu[0].setString("Play");
	
	
	menu[1].setFont(font);
	menu[1].setFillColor(sf::Color::White);
	menu[1].setString("About");
	
	
	menu[2].setFont(font);
	menu[2].setFillColor(sf::Color::White);
	menu[2].setString("Exit");
	
	int maxItems = menu.size();
	menu[2].setPosition(sf::Vector2f(width / 2, height / (maxItems +1) * 2));
	menu[1].setPosition(sf::Vector2f(width / 2, height / (maxItems +1) * 1.5));
	menu[0].setPosition(sf::Vector2f(width / 2, height / (maxItems +1) * 1));
	selectedItemId = 0;
}

Menu::~Menu()
{
}

void Menu::draw(sf::RenderWindow& window)
{
	for (unsigned int i = 0; i< menu.size(); i++)
	{
		window.draw(menu[i]);
	}
}
