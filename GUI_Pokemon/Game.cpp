#include "Game.h"
#include <iostream>
#include "Wilderness.h"

Game::Game()
{
	// backend backPack instance
	b = Batoh();
	// backend trener
	t = Trener();

	// graphical backpack
	batoh = BackPack();


}

Game::Game(int& W, int& H)
{
	this->W = W;
	this->H = H;

	//textures
	tMainBG.loadFromFile("../Images/MainBG.jpg");
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

	// graphical backpack
	batoh = BackPack(W, H, b, &t);
	// wilderness
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

void Game::Play(sf::RenderWindow& app)
{
	Player player = Player(t);

	// wilderness
	Wilderness divocina = Wilderness(player,W, H);

	float x = 300, y = 300;
	float Frame = 0;
	float animSpeed = 0.3;
	int frameCount = 20;
	int mRight=0;
	bool inShop = false;
	// game loop
	while (app.isOpen())
	{				
		
		//sprite animation
		Frame += animSpeed;
		if (Frame>frameCount) Frame -= frameCount;
		mRight = int(Frame) * 95;
		if (mRight > 950) {
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
					batoh.draw(app);
				}
			}
			if (event.type == sf::Event::KeyPressed)
			{
				switch (event.key.code)
				{
				case sf::Keyboard::I:
					std::cout << "BATOH" << std::endl;
					batoh.draw(app);
					break;
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
		app.display();
	}
}
