#pragma once
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>
#include "../../Pokemon/Pokemon/Pokemon.h"
#include "../../Pokemon/Pokemon/Arena.h"
#include "GraphicPokemon.h"


class Player;

class FightAnime
{
	sf::Texture pokHealthBar, hitTexture, battle_t;
	sf::Sprite upperPok, bottomPok, healthUp, healthBot, hit;
	sf::Sprite battle;


	sf::Text nameP1, nameP2, damage, Intro;
	sf::Font font;

	GraphicPokemon * gPok1;
	GraphicPokemon * gPok2;

	//Pokemon& pokemon1;
	//Pokemon& pokemon2;

	Arena* souboj;
	Player& player;
	sf::Time time;

	bool pokemonCaught;

public:
	
	//FightAnime(Player& p, Pokemon& pok1, Pokemon& pok2, sf::RenderWindow& app);
	
	void initGraphics();
	
	FightAnime(Player& p,GraphicPokemon& pok1, GraphicPokemon& pok2, sf::RenderWindow& app);
	
	~FightAnime();

	float pok1Attack();
	float pok2Attack();
	void animateBattle(float animSpeed, int frameCount, float& FrameB, int mRightB);
	void animateIntroOfFight(sf::RenderWindow& app, sf::Clock clock);

	bool getResult()
	{
		return pokemonCaught;
	}
	void draw(sf::RenderWindow & app);
	void drawForStadium(sf::RenderWindow& app);
};

