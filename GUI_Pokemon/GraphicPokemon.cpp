#include "GraphicPokemon.h"
#include <ctime>

GraphicPokemon::GraphicPokemon(Pokemon* pokemon)
{
	// pointer to pokemon
	pokemon_ = pokemon;
	std::string name = pokemon_->getJmeno();
	
	// texture
	texture_.loadFromFile("../Images/pokemons/" + name + ".png");
	texture_.setSmooth(true);
	// sprite
	setTexture(texture_);
	setTextureRect(sf::IntRect(0, 0, 32, 32));
}

GraphicPokemon::~GraphicPokemon()
{
}
// zmenit parametry!!!!!!!!!!!!!!
int GraphicPokemon::randomWalk(float& x, float& y, int& mRight, int mx, int my)
{
	// seed
	srand(time(NULL));
	
	// random number 1 - 5
	int rand = ::rand() % 5 +1;

	switch (rand)
	{
	// stay
	case 1:
		break;
	//up
	case 2:
		setTextureRect(sf::IntRect(mRight, 96, 32, 32));
		break;
	//right
	case 3:
		setTextureRect(sf::IntRect(mRight, 64, 32, 32));
		break;
	//down
	case 4:
		setTextureRect(sf::IntRect(mRight, 0, 32, 32));
		break;
	//left
	case 5:
		setTextureRect(sf::IntRect(mRight, 32, 32, 32));
		break;
	default:
		break;
	}
	return rand;
}
