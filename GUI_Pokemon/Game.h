#pragma once
#include <SFML/Window/Keyboard.hpp>
#include "SFML/Graphics.hpp"
#include "Player.h"
#include "BackPack.h"
#include "GraphicPokemon.h"


class Game
{
protected:
	
private:
	float W, H;
	// backend backPack instance
	Batoh b;
	// backend trener
	Trener t;

	sf::FloatRect exits[3];
	sf::FloatRect movingArea;

	// Textures
	sf::Texture tHuman, tShop, tMainBG, tShopBG, tBackPack, tControls;
	// Sprites
	sf::Sprite sShop, sMainBG, sShopBG, sBackPack, sControls;
	sf::Text help;
	sf::Font font;
public:

	

	Game();
	Game(int& W, int& H);
	~Game();
	int movePlayer(Player& sPlayer, int& mRight, int mx, int my, int disabledDirection);
	
	bool Collide(sf::Sprite &s1, sf::Sprite &s2);
	bool setViewCenter(Player& player, sf::View& view, float vx, float vy);
	void initView(sf::View& view);
	void Play(sf::RenderWindow &app);
	Trener& getTrener();

};

