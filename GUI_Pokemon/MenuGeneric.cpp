#include "MenuGeneric.h"
#include <iostream>

MenuGeneric::MenuGeneric()
{
	if (!font.loadFromFile("../Fonts/arial.ttf"))
	{
		std::cout << "font not loaded" << std::endl;
	}
	menu.clear();
	selectedItemId = 0;
}

MenuGeneric::~MenuGeneric()
{
}

void MenuGeneric::moveUp()
{
	if (selectedItemId - 1 >= 0)
	{
		menu[selectedItemId].setFillColor(sf::Color::White);
		selectedItemId--;
		menu[selectedItemId].setFillColor(sf::Color::Red);
	}
}

void MenuGeneric::moveDown()
{
	if (selectedItemId + 1 < menu.size())
	{
		menu[selectedItemId].setFillColor(sf::Color::White);
		selectedItemId++;
		menu[selectedItemId].setFillColor(sf::Color::Red);
	}
}

int MenuGeneric::getPressedItem() const
{
		return selectedItemId;
}
