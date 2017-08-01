#pragma once
#include "Player.h"
#include <iostream>

struct Statistic
{
		int *penize;
		int *pokebaly;
		int *potiony;

		sf::Texture texture_;
		sf::Text penizeT, pokebalyT, potionyT;
		sf::Sprite statBar;
		sf::Font font;

public:
	Statistic(Player& player)
	{
		penize = player.getBackEndTrener()->getPointerToMoney();
		pokebaly = player.getBackEndTrener()->getBatoh().getPointerToPokeball();
		potiony = player.getBackEndTrener()->getBatoh().getPointerToPotion();

		if (!texture_.loadFromFile("../Images/playerTools/statistic.png"))
		{
			std::cerr << "texture not loaded - STATISTIC" << std::endl;
		}

		statBar.setTexture(texture_);

		
		font.loadFromFile("../Fonts/arial.ttf");

		penizeT.setFont(font);
		pokebalyT.setFont(font);
		potionyT.setFont(font);		
		
		penizeT.setCharacterSize(9);
		pokebalyT.setCharacterSize(9);
		potionyT.setCharacterSize(9);

		penizeT.setFillColor(sf::Color::Black);
		pokebalyT.setFillColor(sf::Color::Black);
		potionyT.setFillColor(sf::Color::Black);
	}

	~Statistic()
	{
		
	}

	void drawStatistic(sf::RenderWindow& app, sf::Vector2f position)
	{
		penizeT.setString(std::to_string(*penize));
		pokebalyT.setString(std::to_string(*pokebaly));
		potionyT.setString(std::to_string(*potiony));
		
		statBar.setPosition(position + sf::Vector2f(120, -145));
		penizeT.setPosition(statBar.getPosition() + sf::Vector2f(13, 3));
		pokebalyT.setPosition(statBar.getPosition() + sf::Vector2f(46, 3));
		potionyT.setPosition(statBar.getPosition() + sf::Vector2f(74, 3));

		app.draw(statBar);
		app.draw(penizeT);
		app.draw(pokebalyT);
		app.draw(potionyT);

	}
	
};

