#include "GraphicPokemon.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include <iostream>


GraphicPokemon::GraphicPokemon(Pokemon* pokemon, float x, float y)
{
	
	//default position
	this->x = x;
	this->y = y;
	
	// pointer to pokemon
	pokemon_ = pokemon;
	std::string name = pokemon_->getJmeno();
	
	// texture
	if (!texture_.loadFromFile("../Images/pokemons/" + name + ".png"))
	{
		std::cerr << "texture not loaded";
	}
	
	texture_.setSmooth(true);
	// sprite
	setTexture(texture_);
	setTextureRect(sf::IntRect(0, 0, 32, 32));
	// direction of last move
	lastDirection = 0;
	// initialize circle shaped surrounding area
	surroundings.setRadius(35);
	surroundings.setFillColor(sf::Color::Green);

	setPosition(this->x, this->y);

}

GraphicPokemon::GraphicPokemon()
{
}

GraphicPokemon::~GraphicPokemon()
{
}

void GraphicPokemon::refactorCoordinates()
{
	// check for boundaries
	if (x > 1130) x = 1129;
	if (y > 750) y = 749;
	if (x < 10) x = 10;
	if (y < 16) y = 16;
}

int GraphicPokemon::randomWalk(int& mRight, int mx, int my, int randNum)
{
		
	// random number 1 - 5
	int rand = randNum;

	switch (rand)
	{
	// stay
	case 1:
		break;
	//up
	case 2:
		setTextureRect(sf::IntRect(mRight, 96, 30, 30));
		y += my;
		break;
	//right
	case 3:
		setTextureRect(sf::IntRect(mRight, 64, 30, 30));
		x += mx;
		break;
	//down
	case 4:
		setTextureRect(sf::IntRect(mRight, 0, 30, 30));
		y -= my;
		break;
	//left
	case 5:
		setTextureRect(sf::IntRect(mRight, 32, 30, 30));
		x -= mx;
		break;
	default:
		break;
	}

	refactorCoordinates();

	lastDirection = rand;
	return rand;
}

void GraphicPokemon::walk(int mRight, int mx, int my)
{
	switch (lastDirection)
	{
		//up
	case 2:
		setTextureRect(sf::IntRect(mRight, 96, 30, 30));
		y -= my;
		break;
		//right
	case 3:
		setTextureRect(sf::IntRect(mRight, 64, 30, 30));
		x += mx;
		break;
		//down
	case 4:
		setTextureRect(sf::IntRect(mRight, 0, 30, 30));
		y += my;
		break;
		//left
	case 5:
		setTextureRect(sf::IntRect(mRight, 32, 30, 30));
		x -= mx;
		break;
	default:
		break;
	}
	
	refactorCoordinates();
}

void GraphicPokemon::avoidNeighbours(int mRight, int mx, int my)
{
	switch (lastDirection)
		{
			//up -> down
		case 2:
			setTextureRect(sf::IntRect(mRight, 0, 30, 30));
			y += my;
			break;
			//right -> left
		case 3:
			setTextureRect(sf::IntRect(mRight, 32, 30, 30));
			x -= mx; 
			break;
			//down -> up
		case 4:
			setTextureRect(sf::IntRect(mRight, 96, 30, 30));
			y -= my;
			break;
			//left -> right
		case 5:
			setTextureRect(sf::IntRect(mRight, 64, 30, 30));
			x += mx;
			break;
		default:
			break;
		}
	refactorCoordinates();
}

sf::String GraphicPokemon::getID()
{
	return pokemon_->getJmeno();
}

sf::FloatRect GraphicPokemon::getSurroundings()
{
	surroundings.setPosition(x - 24, y - 24);
	return surroundings.getGlobalBounds();
}

