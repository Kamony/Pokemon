#pragma once
#include <vector>
#include "../../Pokemon/Pokemon/Pokemon.h"
#include "../../Pokemon/Pokemon/Divocina.h"
#include "GraphicPokemon.h"
#include "Game.h"

namespace sf {
	class RenderWindow;
}



class Wilderness: public Game
{
private:
	std::vector<GraphicPokemon> listOfGraphicsPokemon;
	Divocina *divocina;
	sf::Texture texture_;
	sf::Sprite sprite_;

	float W, H;

	// seed random generator
	std::mt19937 rng;

public:
	Wilderness(float w, float h);
	~Wilderness();

	void draw(sf::RenderWindow &app);
};

