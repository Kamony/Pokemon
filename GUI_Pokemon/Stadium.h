#pragma once
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>
#include "Player.h"
#include "../../Pokemon/Pokemon/Stadion.h"
#include "Game.h"
#include "GraphicPokemon.h"

class Stadium : public Game
{
	sf::Texture bg_texture, articuno_texture, zapdos_texture, moltres_texture, champ_texture, crown_texture;
	sf::Sprite bg, champ, crown;
	GraphicPokemon *articuno, *zapdos, *moltres;
	sf::Text text, victoryText;
	sf::Font font;

	bool art_alive, zap_alive, molt_alive;
	sf::FloatRect movingArea,exit;

	Player& player;
	Stadion stadionBackEnd;
	
public:
	Stadium(Player& player);
	~Stadium();
	void disablePokemon(GraphicPokemon& pok);
	void drawEndOfGame(sf::RenderWindow& app);
	void drawAfterVictory(sf::RenderWindow& app, float& FrameCrown, int& CmRight);

	void draw(sf::RenderWindow& app);
};

