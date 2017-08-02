#pragma once
#include "../../Pokemon/Pokemon/Batoh.h"
#include "SFML/Graphics.hpp"
#include "../../Pokemon/Pokemon/Trener.h"
#include "MenuGeneric.h"
#include "GraphicPokemon.h"
#include "Player.h"


class ListOfPokemon: public MenuGeneric
{
private:
	sf::Texture bg_texture;
	sf::Sprite bg;

	unsigned int sum;
	Trener* trener;
	std::vector<GraphicPokemon> list;
public:
	ListOfPokemon(float w, float h, Player &player);
	~ListOfPokemon();

	void draw(sf::RenderWindow &window);
	int drawForBattle(sf::RenderWindow& window);
};

