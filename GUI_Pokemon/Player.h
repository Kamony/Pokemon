#pragma once
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include "../../Pokemon/Pokemon/Trener.h"
#include "GraphicPokemon.h"

class Player: public sf::Sprite
{
private:
	// textures
	sf::Texture texture_, battleTexture;
	// sprite
	Sprite battle;
	/// position coordinates
	float x, y;
	/// collision area;
	sf::RectangleShape surroundings;
	/// direction of player is moving
	int direction;

	Trener& trener;


	std::vector<GraphicPokemon> list;

public:
	Player();
	Player(Trener& trener);
	~Player();

	/**
	 * \brief move player to position
	 * \param mRight changing upper left x coordinate
	 * \param mx shift of x coordinate
	 * \param my shift of y coordinate
	 * \param direction 1-up 2-down 3-left 4-right
	 */
	void walk(int direction, int mRight, int mx, int my);
	/**
	 * \brief sets position of Player and his surrounding area
	 * \param x x coordinate
	 * \param y y coordinate
	 */
	void setPosition(float x, float y);
	/**
	 * \brief Get surrounding area of Player
	 * \return GlobalBounds()
	 */
	sf::FloatRect getSurroundings();

	/**
	 * \brief get rectangle shaped surroundings
	 * \return surroundings
	 */
	sf::RectangleShape getCollideArea()
	{
		return surroundings;
	}
	bool catchPok(sf::RenderWindow& app, sf::Vector2f position, Pokemon& pokemon);

	void addGraphicPokemon(GraphicPokemon& pokemon)
	{
		list.push_back(pokemon);
	}

	void synchronizeFrontAndBackEnd();

	Trener* getBackEndTrener()
	{
		return &trener;
	}

	std::vector<GraphicPokemon>& getGraphicPokemonList()
	{
		return list;
	}

	GraphicPokemon* choosePokemon(sf::RenderWindow& app);
};

