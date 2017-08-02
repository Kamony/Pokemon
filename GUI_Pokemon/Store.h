#pragma once
#include "MenuGeneric.h"
#include "../../Pokemon/Pokemon/Obchod.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include "Player.h"

class Store : public MenuGeneric
{
	Obchod obchod;
	sf::Texture bg_texture;
	sf::Sprite bg;
	sf::Text money, buyPokebal, buyPotion, stav, returnButton;

	Player* player;

public:
	Store(Player &player);
	~Store();

	void draw(sf::RenderWindow& app);
};

