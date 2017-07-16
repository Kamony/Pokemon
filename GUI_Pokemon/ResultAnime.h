#pragma once
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include "GraphicPokemon.h"

class ResultAnime
{
	sf::Text winner, name, backButton, resultOfCatch;
	sf::Font font;
	sf::Texture pokeball_t;
	sf::Sprite pokeball;
	sf::Time time;
	bool backNotPressed;
public:
	/**
	 * \brief 
	 * \param nameOfWinner winner pokemons name
	 * \param loserPok defeated pokemon
	 * \param app window
	 * \param stav 1 - player win; 2 - tie; 3 - player lost 
	 */
	ResultAnime(std::string nameOfWinner, GraphicPokemon& loserPok, sf::RenderWindow& app,int stav);
	~ResultAnime();

	void draw(sf::RenderWindow& app, GraphicPokemon& loser, int stav);
};

