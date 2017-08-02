#pragma once
#include <SFML/Graphics/Text.hpp>
#include "../../Pokemon/Pokemon/Pokemon.h"
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

class PreGame
{
	int chosenPok;
	sf::Font font;
	sf::Text intro, enterButton;
	sf::Texture oakT, bulbT, charT, squirT, bg_texture;
	sf::Sprite oak, bulbasaur,charmander,squirtle, bg;
	sf::RectangleShape area;
	
public:
	PreGame();
	~PreGame();

	int getChosenPok()
	{
		return chosenPok;
	}

	void draw(sf::RenderWindow& app);
};

