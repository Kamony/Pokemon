#include "GraphicPokemon.h"
#include <ctime>
#include <random>



GraphicPokemon::GraphicPokemon(Pokemon* pokemon, std::mt19937 rng)
{
	this->rng();
	//this->rng = rng;
	
	// distribution that maps 1 - 5
	std::uniform_int_distribution<> randomXcoordinate(1, 1200);
	std::uniform_int_distribution<> randomYcoordinate(1, 800);
	
	
	//default position
	this->x = randomXcoordinate(this->rng);
	this->y = randomYcoordinate(this->rng);
	
	// pointer to pokemon
	pokemon_ = pokemon;
	std::string name = pokemon_->getJmeno();
	
	// texture
	texture_.loadFromFile("../Images/pokemons/" + name + ".png");
	texture_.setSmooth(true);
	// sprite
	setTexture(texture_);
	setTextureRect(sf::IntRect(0, 0, 32, 32));

	this->rng();
	rng.seed();
	randomXcoordinate.reset();
	randomYcoordinate.reset();
}

GraphicPokemon::~GraphicPokemon()
{
}

int GraphicPokemon::randomWalk(int& mRight, int mx, int my)
{
	// distribution that maps 1 - 5
	std::uniform_int_distribution<> five(1, 5);

	
	// random number 1 - 5
	int rand = five(rng);

	switch (rand)
	{
	// stay
	case 1:
		break;
	//up
	case 2:
		setTextureRect(sf::IntRect(mRight, 96, 32, 32));
		y += my;
		break;
	//right
	case 3:
		setTextureRect(sf::IntRect(mRight, 64, 32, 32));
		x += mx;
		break;
	//down
	case 4:
		setTextureRect(sf::IntRect(mRight, 0, 32, 32));
		y -= my;
		break;
	//left
	case 5:
		setTextureRect(sf::IntRect(mRight, 32, 32, 32));
		x -= mx;
		break;
	default:
		break;
	}

	// check for boundaries
	if (x > 1199) x = 1;
	if (y > 799) y = 1;
	if (x < 1) x = 1199;
	if (y < 1) y = 799;


	return rand;
}
