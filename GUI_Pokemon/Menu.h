#pragma once
#include "SFML/Graphics.hpp"
#include "MenuGeneric.h"


class Menu:public MenuGeneric
{
	sf::Texture bg_texture;
	sf::Sprite bg;
private:
	public:
	Menu(float width, float height);
	~Menu();
	void draw(sf::RenderWindow &window);

	void moveUp() override;
	void moveDown() override;
};

