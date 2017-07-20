#pragma once
#include <SFML/Window/Keyboard.hpp>
#include "SFML/Graphics.hpp"
#include "Player.h"
#include "BackPack.h"


class Game
{
protected:
	
private:
	float W, H;
	// backend backPack instance
	Batoh b;
	// backend trener
	Trener t;

	
public:
	
	// Textures
	sf::Texture tHuman, tShop, tMainBG, tShopBG, tBackPack;
	// Sprites
	sf::Sprite sShop, sMainBG, sShopBG, sBackPack;
	

	Game();
	Game(int& W, int& H);
	~Game();
	void movePlayer(Player& sPlayer, int& mRight, int mx, int my);
	
	bool Collide(sf::Sprite &s1, sf::Sprite &s2);
	bool setViewCenter(Player& player, sf::View& view, float vx, float vy);
	void Play(sf::RenderWindow &app);
};

