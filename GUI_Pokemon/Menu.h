#pragma once
#include "SFML/Graphics.hpp"
#include "MenuGeneric.h"


class Menu:public MenuGeneric
{
private:
	public:
	Menu(float width, float height);
	~Menu();
	void draw(sf::RenderWindow &window);
	

};

