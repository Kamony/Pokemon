#pragma once
#include "../../Pokemon/Pokemon/Batoh.h"
#include "SFML/Graphics.hpp"
#include "../../Pokemon/Pokemon/Trener.h"
#include "MenuGeneric.h"

class ListOfPokemon: public MenuGeneric
{
private:
	unsigned int sum;
	Trener* trener;

public:

	ListOfPokemon(float w, float h, std::vector<Pokemon>& list, Trener* trener);
	~ListOfPokemon();

	void draw(sf::RenderWindow &window);

};

