#pragma once
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include "../../Pokemon/Pokemon/Pokemon.h"
#include <random>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/CircleShape.hpp>

class GraphicPokemon : public sf::Sprite
{
private:
	//texture
	sf::Texture texture_;
	// pointer to object pokemon
	Pokemon *pokemon_;
	// position coordinates
	float x, y;
	int lastDirection;
	// area for colision avoidance
	sf::CircleShape surroundings;
	
public:
	GraphicPokemon(Pokemon* pokemon, float x, float y);
	~GraphicPokemon();
	
	void refactorCoordinates();

	int randomWalk(int& mRight, int mx, int my, int rand);

	void walk(int mRight, int mx, int my);

	bool checkForNeighbours(int mRight, int mx, int my);

	void setX(float x){	this->x = x; }

	void setY(float y){	this->y = y; }

	sf::String getID();

	float getX()
	{
		return x;
	}

	float getY()
	{
		return y;
	}

	sf::FloatRect getSurroundings();
};

