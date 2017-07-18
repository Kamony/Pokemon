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

	Player& player;

public:
	Wilderness();
	void initWilderness(std::uniform_int_distribution<> randomXcoordinate, std::uniform_int_distribution<> randomYcoordinate);
	Wilderness(Player& p ,float w, float h);
	~Wilderness();
	void deletePokemon(Pokemon& p);
	void draw(sf::RenderWindow &app);
};

