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
	sf::Texture bg_texture, articuno_texture, zapdos_texture, moltres_texture, champ_texture;
	sf::Sprite bg, champ;
	GraphicPokemon *articuno, *zapdos, *moltres;
	sf::Text text, victoryText;
	sf::Font font;

	bool art_alive, zap_alive, molt_alive;

	Player& player;
	Stadion stadionBackEnd;
	
public:
	Stadium(Player& player);
	~Stadium();

	void draw(sf::RenderWindow& app);
};

