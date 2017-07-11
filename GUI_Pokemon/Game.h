#pragma once
#include <SFML/Window/Keyboard.hpp>
#include "SFML/Graphics.hpp"
#include "Player.h"

class Game
{
private:
	float W, H;
public:

	sf::Keyboard::Key key;
	sf::Keyboard::Key previousKey;
	// Textures
	sf::Texture tHuman, tShop, tMainBG, tShopBG, tBackPack;
	// Sprites
	sf::Sprite sShop, sMainBG, sShopBG, sBackPack;
	

	Game();
	Game(int& W, int& H);
	~Game();
	void movePlayer(Player& sPlayer, int& mRight, int mx, int my);
	
	bool Collide(sf::Sprite &s1, sf::Sprite &s2);
	void Play(sf::RenderWindow &app);
};

