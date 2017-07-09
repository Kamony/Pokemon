#pragma once
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include "../../Pokemon/Pokemon/Pokemon.h"
#include <random>

class GraphicPokemon : public sf::Sprite
{
private:
	//texture
	sf::Texture texture_;
	// pointer to object pokemon
	Pokemon *pokemon_;
	// position coordinates
	float x, y;
	// seed random generator
	std::mt19937 rng;
	
public:
	GraphicPokemon(Pokemon* pokemon, std::mt19937 rng);
	~GraphicPokemon();

	int randomWalk(int& mRight, int mx, int my);

	void setX(float x){	this->x = x; }

	void setY(float y){	this->y = y; }

	float getX()
	{
		return x;
	}

	float getY()
	{
		return y;
	}
};

