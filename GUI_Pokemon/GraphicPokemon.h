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
	sf::Texture texture_, battle;
	// pointer to object pokemon
	Pokemon *pokemon_;
	// position coordinates
	float x, y;
	int lastDirection;
	// area for colision avoidance
	sf::CircleShape surroundings;

	float utok;
	
public:

	GraphicPokemon(Pokemon* pokemon, float x, float y);
	GraphicPokemon();
	~GraphicPokemon();
	
	/**
	 * \brief sets coordinates not to overlap actual size of window 
	 */
	void refactorCoordinates();

	/**
	 * \brief walk in random direction
	 * \param mRight 
	 * \param mx 
	 * \param my 
	 * \param rand 
	 * \return 
	 */
	int randomWalk(int& mRight, int mx, int my, int rand);

	/**
	 * \brief walk in direction saved in object param. lastDirection
	 * \param mRight 
	 * \param mx 
	 * \param my 
	 */
	void walk(int mRight, int mx, int my);

	/**
	 * \brief revert from neighbour
	 * \param mRight 
	 * \param mx 
	 * \param my 
	 * \return 
	 */
	void avoidNeighbours(int mRight, int mx, int my);

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

	Pokemon getPokemon()
	{
		return *pokemon_;
	}


	/**
	 * \brief get collision bounds
	 * \return surrounding area's bounds
	 */
	sf::FloatRect getSurroundings();

	void setForBattle(float utok);
};

