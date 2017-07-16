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
	sf::Texture pokHealthBar, hitTexture, battle_t;
	sf::Sprite upperPok, bottomPok, healthUp, healthBot, hit;
	sf::Sprite battle;


	sf::Text nameP1, nameP2, damage;
	sf::Font font;

	GraphicPokemon * gPok1;
	GraphicPokemon * gPok2;

	Pokemon& pokemon1;
	Pokemon& pokemon2;

	Arena* souboj;

	sf::Time time;

public:
	FightAnime(GraphicPokemon& pok1, GraphicPokemon& pok2, sf::RenderWindow& app);
	~FightAnime();

	float pok1Attack();
	float pok2Attack();
	void animateBattle(float animSpeed, int frameCount, float& FrameB, int mRightB);


	void draw(sf::RenderWindow & app);
};

