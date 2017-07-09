#pragma once
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include "../../Pokemon/Pokemon/Pokemon.h"

class GraphicPokemon : public sf::Sprite
{
private:
	sf::Texture texture_;
	//sf::Sprite sprite_;
	Pokemon *pokemon_;

public:
	GraphicPokemon(Pokemon* pokemon);
	~GraphicPokemon();

	int randomWalk(float& x, float& y, int& mRight, int mx, int my);
};

