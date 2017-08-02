#pragma once
#include "SFML/Graphics.hpp"
#include "Player.h"
#include "BackPack.h"
#include "Store.h"



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
	sf::Texture tHuman, tShop, tMainBG, tShopBG, tBackPack,  tStatistic;
	// Sprites
	sf::Sprite sShop, sMainBG, sShopBG, sBackPack,sStatistic;
	sf::Text help, about;
	sf::Font font;
protected:
	sf::Texture tControls;
	sf::Sprite sControls;
public:

	

	Game();
	Game(int& W, int& H);
	~Game();
	

	void initAbout();

	int movePlayer(Player& sPlayer, int& mRight, int mx, int my, int disabledDirection);
	
	bool Collide(sf::Sprite &s1, sf::Sprite &s2);
	bool setViewCenter(Player& player, sf::View& view, float vx, float vy);
	void initView(sf::View& view);
	void handlePlayerMovement(Player& player, int& lastDirectionOfMovement, int mRight, sf::FloatRect movingArea);
	void newGameInit(sf::RenderWindow& app);
	
	void Play(sf::RenderWindow &app);
	void showAbout(sf::RenderWindow& app);

};

