#include "Game.h"
#include <iostream>
#include "Wilderness.h"
#include "PreGame.h"

Game::Game()
{
	// backend backPack instance
	b = Batoh();
	// backend trener
	t = Trener();



}

Game::Game(int& W, int& H)
{
	this->W = W;
	this->H = H;

	//textures
	tMainBG.loadFromFile("../Images/MainBG.jpg.png");
	tShopBG.loadFromFile("../Images/shopBG.png");
	tBackPack.loadFromFile("../Images/backpack.png");
	tBackPack.setSmooth(true);

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
	sBackPack.setTextureRect(sf::IntRect(113, 79, 670, 840));
	sBackPack.scale(0.2, 0.2);
	sBackPack.setPosition(1050, 0);

	// backend backPack instance
	b = Batoh(5, 4);
	// backend trener
	t = Trener(&b);


}


Game::~Game()
{
}

void Game::movePlayer(Player& sPlayer, int& mRight, int mx, int my)
{
	//set movement
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		sPlayer.walk(4, mRight, mx, my);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		sPlayer.walk(3, mRight, mx, my);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		sPlayer.walk(1, mRight, mx, my);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		sPlayer.walk(2, mRight, mx, my);
	}
}

bool Game::Collide(sf::Sprite &s1, sf::Sprite &s2)
{
	return s1.getGlobalBounds().intersects(s2.getGlobalBounds());
	//s1.getGlobalBounds().contains(s2.getOrigin());
}

bool Game::setViewCenter(Player& player, sf::View& view, float vx, float vy)
{
	bool zmena = false;
	
	if ( vx < 200)
	{
		if (vy > 650)
		{
			view.setCenter(200, 650);
			return false;
		}

		if (vy < 150)
		{
			view.setCenter(200, 150);
			return false;
		}

		view.setCenter(200,player.getPosition().y);
		return false;
	}

	if (vx > 1000)
	{
		if (vy > 650)
		{
			view.setCenter(1000, 650);
			return false;
		}

		if (vy < 150)
		{
			view.setCenter(1000, 150);
			return false;
		}
		view.setCenter(1000, player.getPosition().y);
		return false;
	}

	if (vy < 150)
	{
		if (vx > 1000)
		{
			view.setCenter(1000, 150);
			return false;
		}

		if (vx < 200)
		{
			view.setCenter(200, 150);
			return false;
		}		
		view.setCenter(player.getPosition().x, 150);
		return false;
	}

	if (vy > 650)
	{
		if (vx > 1000)
		{
			view.setCenter(1000, 650);
			return false;
		}

		if (vx < 200)
		{
			view.setCenter(200, 650);
			return false;
		}		
		view.setCenter(player.getPosition().x,650);
		return false;
	}
	view.setCenter(player.getPosition());
	return true;
	
}

void Game::Play(sf::RenderWindow& app)
{
	PreGame intro;
	intro.draw(app);

	switch (intro.getChosenPok())
	{
		case 1:
		{
			Pokemon *bulb = new Pokemon("bulbasaur", Pokemon::Travni, 20, 5);
			t.pridejPokemona(*bulb);
			break;
		}
		case 2:
		{
			Pokemon *charm = new Pokemon("charmander", Pokemon::Ohnivy, 30, 4);
			t.pridejPokemona(*charm);
			break;
		}
		case 3:
		{
			Pokemon *squirt = new Pokemon("squirtle", Pokemon::Vodni, 10, 6);
			t.pridejPokemona(*squirt);
			break;
		}
		default:
			break;
	}

	
	
	Player player = Player(t);

	// wilderness
	Wilderness divocina = Wilderness(player,W, H);

	float x = 300, y = 300;
	float Frame = 0;
	float animSpeed = 0.3;
	int frameCount = 20;
	int mRight=0;
	bool inShop = false;


	sf::View view(sf::FloatRect(0, 0, 800, 600));
	view.zoom(0.5f);
	view.setCenter(W / 2, H / 2);
	float vx = 0;
	float vy = 0;
	// game loop
	while (app.isOpen())
	{
		float vx = player.getPosition().x;
		float vy = player.getPosition().y;

		if(setViewCenter(player, view, vx, vy))
		{
			std::cout << "Posun kamery" << std::endl;
		}
		else { std::cout << "Kamera fix" << std::endl; }
		

	

		//player animation
		Frame += animSpeed;
		if (Frame>frameCount) Frame -= frameCount;
		mRight = int(Frame) * 95;
		if (mRight > 1045) {
			mRight = 0;
			Frame = 0.3;
		}
		
		
		
		// handle events
		sf::Event event;
		while (app.pollEvent(event))
		{
			if(event.type == sf::Event::Closed)
			{
				app.close();
			}
			if (event.type == sf::Event::MouseButtonPressed)
			{
				std::cout << "KLICK!";
				if (event.mouseButton.button == sf::Mouse::Left && sBackPack.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y))
				{
					std::cout << "BATOH" << std::endl;
					BackPack batoh = BackPack(W, H, &t);
					batoh.draw(app);
				}
			}
			if (event.type == sf::Event::KeyPressed)
			{
				switch (event.key.code)
				{
				case sf::Keyboard::I:
				{
					std::cout << "BATOH" << std::endl;
					BackPack batoh = BackPack(W, H, &t);
					batoh.draw(app);
					break;
				}
				case sf::Keyboard::W:
					std::cout << "Wild" << std::endl;
					divocina.draw(app);
					break;
				default:
					break;
				}
			}
		}

		movePlayer(player, mRight, 2.5, 2.5);
		
		sShop.setPosition(257, 14);
		sMainBG.setPosition(0, 0);
		//draw
		app.clear();
		app.draw(sMainBG);
		app.draw(sShop);
		app.draw(player.getCollideArea());
		app.draw(player);
		
		app.draw(sBackPack);
		app.setView(view);
		app.display();
	
	}
}
