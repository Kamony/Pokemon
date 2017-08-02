#include "Game.h"
#include <iostream>
#include "Wilderness.h"
#include "PreGame.h"
#include "Stadium.h"
#include "Store.h"
#include "Statistic.h"

Game::Game()
{
	// backend backPack instance
	b = Batoh();
	// backend trener
	t = Trener();
	tControls.loadFromFile("../Images/playerTools/controls.png");
	sControls.setTexture(tControls);
	sControls.setScale(0.6, 0.6);
}

Game::Game(int& W, int& H)
{
	this->W = W;
	this->H = H;

	//textures
	
	if (!tControls.loadFromFile("../Images/playerTools/controls.png") ||
		!tMainBG.loadFromFile("../Images/MainBG.jpg.png") ||
		!tStatistic.loadFromFile("../Images/playerTools/statistic.png") ||
		!tBackPack.loadFromFile("../Images/backpack.png"))
	{
		std::cerr << "textury nenacteny - GAME" << std::endl;
	}

	tBackPack.setSmooth(true);

	// Main background
	sMainBG.setTexture(tMainBG);
	sMainBG.setTextureRect(sf::IntRect(0, 0, W, H));
	sMainBG.setOrigin(0, 0);
	
	// backpack
	sBackPack.setTexture(tBackPack);
	sBackPack.setTextureRect(sf::IntRect(113, 79, 670, 840));
	sBackPack.setScale(0.05, 0.05);
	
	sControls.setTexture(tControls);
	sControls.setScale(0.6, 0.6);

	sStatistic.setTexture(tStatistic);

	if (!font.loadFromFile("../Fonts/arial.ttf"))
	{
		std::cerr << "font nenacten" << std::endl;
	}

	help.setFont(font);
	help.setString("Hold 'C' to show controls");
	help.setFillColor(sf::Color::Black);

	help.setCharacterSize(11);
	// backend backPack instance
	b = Batoh(5, 4);
	// backend trener
	t = Trener(&b);
	

	movingArea = sf::FloatRect(130, 106, 1029, 638);

	//wild
	exits[0] = sf::FloatRect(132, 39, 45, 60);
	//stadium
	exits[1] = sf::FloatRect(619, 56, 45, 50);
	//shop
	exits[2] = sf::FloatRect(1093, 700, 45, 50);
}


Game::~Game()
{
}

int Game::movePlayer(Player& sPlayer, int& mRight, int mx, int my, int disabledDirection)
{
	//set movement
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && disabledDirection != 4)
	{
		sPlayer.walk(4, mRight, mx, my);
		return 4;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && disabledDirection != 3)
	{
		sPlayer.walk(3, mRight, mx, my);
		return 3;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && disabledDirection != 1)
	{
		sPlayer.walk(1, mRight, mx, my);
		return 1;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && disabledDirection != 2)
	{
		sPlayer.walk(2, mRight, mx, my);
		return 2;
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

void Game::initView(sf::View& view)
{
		
	view.setSize(800, 600);
	view.zoom(0.5f);
	view.setCenter(W / 2, H / 2);
}

void Game::handlePlayerMovement(Player& player, int& lastDirectionOfMovement, int mRight, sf::FloatRect movingArea)
{
	if (movingArea.intersects(player.getSurroundings()))
	{
		lastDirectionOfMovement = movePlayer(player, mRight, 2.5, 2.5, 0);
	}
	else { movePlayer(player, mRight, 2.5, 2.5, lastDirectionOfMovement); }
}

void Game::newGameInit(sf::RenderWindow& app)
{
	PreGame intro;
	intro.draw(app);
		
	switch (intro.getChosenPok())
	{
	case 1:
		{
			Pokemon *bulb = new Pokemon("Bulbasaur", Pokemon::Travni, 20, 5);
			t.pridejPokemona(*bulb);
			
			break;
		}
	case 2:
		{
			Pokemon *charm = new Pokemon("Charmander", Pokemon::Ohnivy, 30, 4);
			t.pridejPokemona(*charm);
			
			break;
		}
	case 3:
		{
			Pokemon *squirt = new Pokemon("Squirtle", Pokemon::Vodni, 10, 6);
			t.pridejPokemona(*squirt);
			
			break;
		}
	default:
			
		break;
	}
}



void Game::Play(sf::RenderWindow& app)
{
	newGameInit(app);
	
	
	//test
	t.pridejPokemona(Pokemon("bababa", Pokemon::Elektricky, 50, 30));
	t.pridejPokemona(Pokemon("b321321aba", Pokemon::Elektricky, 50, 30));
	t.pridejPokemona(Pokemon("bababfdsfa", Pokemon::Elektricky, 50, 30));
	t.pridejPokemona(Pokemon("babahhba", Pokemon::Elektricky, 50, 30));
	t.pridejPokemona(Pokemon("babadfsdba", Pokemon::Elektricky, 50, 30));

	//konec test



	Player player = Player(t);
	player.synchronizeFrontAndBackEnd();
	// statistic of Player - status bar
	Statistic statOfPlayer = Statistic(player);	
	//stadium
	Stadium stadium(player);
	// store
	Store store(player);
	// wilderness
	Wilderness divocina = Wilderness(player,W, H);


	float Frame = 0;
	float animSpeed = 0.3;
	int frameCount = 20;
	int mRight=0;
	bool inShop = false;
	int countOfC = 0;
	int lastDirectionOfMovement = 0;

	sf::View view;
	initView(view);

	
	
	// game loop
	while (app.isOpen())
	{
		
		// handle events
		sf::Event event;
		while (app.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				app.close();
			}

			if (event.type == sf::Event::KeyPressed)
			{
				switch (event.key.code)
				{
				case sf::Keyboard::I:
				{
					std::cout << "BATOH" << std::endl;
					BackPack batoh = BackPack(W, H, player, &t);
					app.setView(app.getDefaultView());
					batoh.draw(app);
					break;
				}
				case sf::Keyboard::S:
				{
					std::cout << "SHOP" << std::endl;
					app.setView(app.getDefaultView());
					store.draw(app);
					break;
				}
				case sf::Keyboard::W:
					std::cout << "Wild" << std::endl;
					app.setView(app.getDefaultView());
					divocina.draw(app);
					break;
				case sf::Keyboard::C:
				{
					sControls.setPosition(view.getCenter() + sf::Vector2f(-130, -135));
					break;
				}
				default:
					break;
				}
			}
		}
				
		float vx = player.getPosition().x;
		float vy = player.getPosition().y;

		setViewCenter(player, view, vx, vy);
				
		help.setPosition(view.getCenter() + sf::Vector2f(-190, -145));

		//player animation
		Frame += animSpeed;
		if (Frame>frameCount) Frame -= frameCount;
		mRight = int(Frame) * 95;
		if (mRight > 1045) {
			mRight = 0;
			Frame = 0.3;
		}
		
		handlePlayerMovement(player, lastDirectionOfMovement, mRight, movingArea);
		
		
		sMainBG.setPosition(0, 0);

		// handle shifts of places
		if (exits[0].intersects(player.getSurroundings()))
		{
			std::cout << "Wild" << std::endl;
			app.setView(app.getDefaultView());
			divocina.draw(app);

		}else
			if (exits[1].intersects(player.getSurroundings()))
			{
				std::cout << "Stadium" << std::endl;
				app.setView(app.getDefaultView());
				stadium.draw(app);
				
			} else //shop
			{
				if (exits[2].intersects(player.getSurroundings()))
				{
					std::cout << "shop" << std::endl;
					app.setView(app.getDefaultView());
					store.draw(app);
				}
			}

		//draw
		app.clear();
			
		app.draw(sMainBG);

		app.draw(player.getCollideArea());
		app.draw(player);
				
		app.setView(view);
		app.draw(help);

		statOfPlayer.drawStatistic(app, view.getCenter());
		
		app.draw(sBackPack);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::C))
		{
			app.draw(sControls);
		}
		app.display();
	}
}
