#include "Game.h"
#include <iostream>
#include "BackPack.h"
#include "Wilderness.h"


Game::Game()
{
}

Game::Game(int& W, int& H)
{
	this->W = W;
	this->H = H;
	
	//textures
	tHuman.loadFromFile("../Images/Human.png");
	tHuman.setSmooth(true);
	tMainBG.loadFromFile("../Images/MainBG.jpg");
	tShopBG.loadFromFile("../Images/shopBG.png");
	tBackPack.loadFromFile("../Images/backpack.png");
	tBackPack.setSmooth(true);
	
	//sprites
	sPlayer.setTexture(tHuman);
	sPlayer.setTextureRect(sf::IntRect(0, 0, 95, 158.75));
	sPlayer.setOrigin(47.5, 150.75);
	sPlayer.scale(0.5, 0.5);

	// Main background
	sMainBG.setTexture(tMainBG);
	sMainBG.setTextureRect(sf::IntRect(0, 0, W, H));
	sMainBG.setOrigin(0, 0);

	// shopBG
	sShopBG.setTexture(tShopBG);
	sShopBG.setTextureRect(sf::IntRect(0, 0, W, H));

	// Shop
	sShop.setTextureRect(sf::IntRect(2, 20, 228, 218));
	// backpack
	sBackPack.setTexture(tBackPack);
	sBackPack.setTextureRect(sf::IntRect(113,79,670,840));
	sBackPack.scale(0.2, 0.2);
	sBackPack.setPosition(1050, 0);
	
}


Game::~Game()
{
}

sf::Keyboard::Key Game::movePlayer(sf::Sprite& sPlayer, float& x, float& y, int& mRight, int mx, int my)
{
	//set movement
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		key = sf::Keyboard::Right;
		x += mx;
		sPlayer.setTextureRect(sf::IntRect(mRight, 317.5, 95, 158.75));
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		key = sf::Keyboard::Left;
		x -= mx;
		sPlayer.setTextureRect(sf::IntRect(mRight, 158.75, 95, 158.75));
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		key = sf::Keyboard::Up;
		y -= my;
		sPlayer.setTextureRect(sf::IntRect(mRight, 476.25, 95, 158.75));
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		key = sf::Keyboard::Down;
		y += my;
		sPlayer.setTextureRect(sf::IntRect(mRight, 0, 95, 158.75));
	}
	return key;
}

bool Game::Collide(sf::Sprite &s1, sf::Sprite &s2)
{
	return s1.getGlobalBounds().intersects(s2.getGlobalBounds());
	//s1.getGlobalBounds().contains(s2.getOrigin());
}

void Game::Play(sf::RenderWindow& app)
{
	// backPack instance
	Batoh b(5,4);
	Trener t(&b);
	Pokemon* prvni = new Pokemon("test1", Pokemon::Elektricky, 20, 30);
	Pokemon* druhy = new Pokemon("test2", Pokemon::Elektricky, 15, 25);
	t.pridejPokemona(*prvni);
	t.pridejPokemona(*druhy);
	BackPack batoh(W, H, b, &t);

	// wilderness
	Wilderness divocina(W,H);
	
	float x = 300, y = 300;
	float Frame = 0;
	float animSpeed = 0.3;
	int frameCount = 20;
	int mRight=0;
	bool inShop = false;
	// game loop
	while (app.isOpen())
	{				
		// handle events
		sf::Event event;
		while (app.pollEvent(event))
		{
			if(event.type == sf::Event::Closed)
			{
				app.close();
			}
			if (event.type == sf::Event::MouseButtonPressed)
				std::cout << "KLICK!";
				if (event.mouseButton.button == sf::Mouse::Left && sBackPack.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y))
				{
					std::cout << "BATOH" << std::endl;
					batoh.draw(app);
				}
			if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::I)
				{
					std::cout << "BATOH" << std::endl;
					batoh.draw(app);
				}
			}
				break;
		}

		//sprite animation
		Frame += animSpeed;
		if (Frame>frameCount) Frame -= frameCount;
		mRight = int(Frame) * 95;
		if (mRight > 950) {
			mRight = 0;
			Frame = 0.3;
		}
		
		//collision detection
		if (!Collide(sShop,sPlayer))
		{
			previousKey = movePlayer(sPlayer, x, y, mRight, 3, 3);
			if (x > W) x = 0; if (x < 0) x = W;
			if (y > H) y = 0; if (y < 0) y = H;
			
		}
		else
		{
			std::cout << "-----COLIDUJEME------" << std::endl;
			key = movePlayer(sPlayer, x, y, mRight, 0, 0);
			if (key == sf::Keyboard::Up && (sPlayer.getGlobalBounds().left < sShop.getGlobalBounds().width))
			{
				std::cout << "V shopu" << std::endl;
				inShop=true;
			}else
			if (movePlayer(sPlayer, x, y, mRight, 0, 0) != previousKey)
			{
				movePlayer(sPlayer, x, y, mRight, 3, 3);
			}
			
		}


		if(inShop)
		{
			//// set coordinates of sprites in shop
			//sShopBG.setPosition(0, 0);
			////draw
			//app.clear();
			//app.draw(sShopBG);

			// set coordinates of sprites in shop
			
			//draw
			std::cout << "Divocina!" << std::endl;
			divocina.draw(app);
		}
		else
		{
			// set coordinates of sprites in main
			sPlayer.setPosition(x, y);
			sShop.setPosition(257, 14);
			sMainBG.setPosition(0, 0);
			//draw
			app.clear();
			app.draw(sMainBG);
			app.draw(sShop);
			app.draw(sPlayer);
		}
		app.draw(sBackPack);
		app.display();
	}
}
