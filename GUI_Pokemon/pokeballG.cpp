#include "pokeballG.h"
#include <iostream>


pokeballG::pokeballG()
{
	x = 0;
	y = 0;
	
	if (!texture_.loadFromFile("../Images/playerTools/pokeball.png"))
	{
		std::cerr << "Texture was not loaded";
	}
	texture_.setSmooth(true);

	setTexture(texture_);
	setTextureRect(sf::IntRect(0, 0, 14, 13));
	isThrown = false;
}


pokeballG::~pokeballG()
{
}

void pokeballG::setInitPosition(sf::Vector2f position)
{
	x = position.x;
	y = position.y;
	initX = x;
	initY = y;
	setPosition(x,y);
	move(sf::Vector2f(35, 40));
}

float pokeballG::getYThrowCoordinate()
{
	float b = (initX+50)/25;
	float ax = -(x*x)/50;
	float c = initY;
			
	float sum = ax + b - c;
	return sum;
}
