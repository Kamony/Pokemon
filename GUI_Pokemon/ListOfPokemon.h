#pragma once
#include "../../Pokemon/Pokemon/Batoh.h"
#include "SFML/Graphics.hpp"
#include "../../Pokemon/Pokemon/Trener.h"
#include "MenuGeneric.h"
#include "GraphicPokemon.h"

class ListOfPokemon: public MenuGeneric
{
private:
	unsigned int sum;
	Trener* trener;
	std::vector<GraphicPokemon>& list;
public:

//	ListOfPokemon(float w, float h, std::vector<Pokemon>& list, Trener* trener);
	ListOfPokemon(float w, float h, std::vector<GraphicPokemon>& list, Trener* trener);
	~ListOfPokemon();

	void draw(sf::RenderWindow &window);
	int drawForBattle(sf::RenderWindow& window);
};

