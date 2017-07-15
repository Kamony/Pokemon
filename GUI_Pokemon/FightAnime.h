#pragma once
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>
#include "../../Pokemon/Pokemon/Pokemon.h"
#include "../../Pokemon/Pokemon/Arena.h"
#include "GraphicPokemon.h"

class FightAnime
{
	sf::Texture pokHealthBar, hitTexture;
	sf::Sprite upperPok, bottomPok, healthUp, healthBot, hit;
	sf::Text nameP1, nameP2, damage;
	sf::Font font;

	Pokemon pokemon1;
	Pokemon pokemon2;

	Arena* souboj;

	sf::Time time;

public:
	FightAnime(GraphicPokemon& pok1, GraphicPokemon& pok2);
	~FightAnime();

	float pok1Attack();
	float pok2Attack();



	void draw(sf::RenderWindow & app);
};

