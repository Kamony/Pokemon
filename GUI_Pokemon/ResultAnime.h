#pragma once
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include "GraphicPokemon.h"
#include "Player.h"

class ResultAnime
{
	sf::Text winner, name, backButton, resultOfCatch, actionButton, continueText;
	sf::Font font;
	sf::Texture pokeball_t, bg_texture;
	sf::Sprite pokeball, bg;
	Player& player;
	bool backNotPressed;
	bool pokemonCaught;
public:
	void initResult(int stav);
	/**
	 * \brief result animation without option to caught pokemon
	 * \param nameOfWinner winner pokemons name
	 * \param loserPok defeated pokemon
	 * \param app window
	 * \param stav 1 - player win; 2 - tie; 3 - player lost 
	 */
	ResultAnime(Player& player,std::string nameOfWinner, GraphicPokemon& loserPok, sf::RenderWindow& app,int stav);
	/**
	 * \brief basic result animation without option to caught pokemon
	 * \param player 
	 * \param app 
	 * \param stav 
	 */
	ResultAnime(Player& player, sf::RenderWindow& app, int stav);

	~ResultAnime();

	void animateResult(sf::RenderWindow& app, int stav, int counter, bool choice);

	bool getResult()
	{
		return pokemonCaught;
	}

	void draw(sf::RenderWindow& app, GraphicPokemon& loser, int stav);
	void drawOnlyResult(sf::RenderWindow& app);
};

