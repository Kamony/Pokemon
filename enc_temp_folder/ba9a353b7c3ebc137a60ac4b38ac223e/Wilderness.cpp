#include "Wilderness.h"
#include <iostream>
#include "pokeballG.h"
#include "FightAnime.h"
#include "ListOfPokemon.h"
#include "Statistic.h"

Wilderness::Wilderness():Game(),player(Player())
{
}

void Wilderness::initWilderness(std::uniform_int_distribution<> randomXcoordinate, std::uniform_int_distribution<> randomYcoordinate)
{
	for (Pokemon& pokemon : divocina->getVectorOfPokemon())
	{
		GraphicPokemon* item = new GraphicPokemon(&pokemon, randomXcoordinate(rng), randomYcoordinate(rng));
		listOfGraphicsPokemon.push_back(*item);
		
	}
}

Wilderness::Wilderness(Player& p,float w, float h) :W(w), H(h),player(p)
{
	rng();
	
	// distributions that maps random coordinates 
	std::uniform_int_distribution<> randomXcoordinate(1, 1200);
	std::uniform_int_distribution<> randomYcoordinate(1, 800);
	

	texture_.loadFromFile("../Images/wildernessBG.png");
	sprite_.setTexture(texture_);
	sprite_.setTextureRect(sf::IntRect(0,0,W,H));
	
	this->divocina = new Divocina();
	initWilderness(randomXcoordinate, randomYcoordinate);

	exit = sf::FloatRect(0, 547, 38, 80);
	movingArea = sf::FloatRect(25, 30, 1125, 735);
}

Wilderness::~Wilderness()
{
}

void Wilderness::deletePokemon(Pokemon& p)
{
	// distributions that maps random coordinates 
	std::uniform_int_distribution<> randomXcoordinate(1, 1200);
	std::uniform_int_distribution<> randomYcoordinate(1, 800);
	
	divocina->odeberPokemona(p);
	listOfGraphicsPokemon.clear();
	initWilderness(randomXcoordinate, randomYcoordinate);
}

void Wilderness::draw(sf::RenderWindow& app)
{
	
	float Frame = 0;
	float animSpeed = 0.15;
	int frameCount = 20;
	int mRight = 0;
	int mRightPlayer = 0;
	float FramePlayer = 0;
	int counter = 0;
	int pokCounter = 0;


	Statistic statOfPlayer = Statistic(player);
	Store store(player);

	
	// distribution that maps 1 - 5
	std::uniform_int_distribution<> five(1, 5);


	sf::View view;
	initView(view);

	player.setPosition(50, 550);

	bool exitNotPressed = true;
	int lastDirectionOfMovement = 0;

	// game loop
	while (exitNotPressed)
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
					BackPack batoh = BackPack(W, H, player, player.getBackEndTrener());
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


		//sprite animation of pokemon
		Frame += animSpeed;
		if (Frame > frameCount) Frame -= frameCount;
		mRight = int(Frame) * 32;
		if (mRight > 70) {
			mRight = 0;
			Frame = 0.3;
		}

		//sprite animation of player
		FramePlayer += animSpeed;
		if (FramePlayer > frameCount) FramePlayer -= frameCount;
		mRightPlayer = int(FramePlayer) * 95;
		if (mRightPlayer > 950) {
			mRightPlayer = 0;
			FramePlayer = 0.3;
		}

	

		handlePlayerMovement(player, lastDirectionOfMovement, mRightPlayer, movingArea);

		sprite_.setPosition(0, 0);

		// go back to main bg
		if (exit.intersects(player.getSurroundings()))
		{
			exitNotPressed = false;
		}

		app.clear();

		app.draw(sprite_);



		if (sf::Keyboard::isKeyPressed(sf::Keyboard::C))
		{
			app.draw(sControls);
		}


		// handle collisions
		for (GraphicPokemon& pokemon : listOfGraphicsPokemon)
		{
			pokemon.setPosition(pokemon.getX(), pokemon.getY());
			for (GraphicPokemon& oPokemon : listOfGraphicsPokemon)
			{
				if (pokemon.getID() != oPokemon.getID())
				{
					sf::FloatRect pok1 = pokemon.getSurroundings();
					sf::FloatRect pok2 = oPokemon.getSurroundings();
					if (pok1.intersects(pok2))
					{
						oPokemon.avoidNeighbours(mRight, 1, 1);
						pokemon.avoidNeighbours(mRight, 1, 1);
					}
				}
			}

			if (player.getSurroundings().intersects(pokemon.getSurroundings()))
			{
				std::cout << "KOLIZE S " << pokemon.getPokemon().getJmeno();
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
				{
					std::cout << "Souboj!";
					app.setView(app.getDefaultView());
					GraphicPokemon* chosenFromPlayer = player.choosePokemon(app);
					if (chosenFromPlayer != nullptr)
					{
						app.setView(app.getDefaultView());
						FightAnime fight(player, *chosenFromPlayer, pokemon, app);
						if (fight.getResult())
						{
							deletePokemon(pokemon.getPokemon());
							player.synchronizeFrontAndBackEnd();
							break;
						}else
							{
								pokemon.setScale(1, 1);
							}
					}
					
				}
			}
			app.draw(pokemon);
		}

		// move pokemon
		if (counter % 20 == 0)
		{
			for (GraphicPokemon& pokemon : listOfGraphicsPokemon) {
				pokemon.randomWalk(mRight, 1, 1, five(rng));

			}
		}
		else
			for (GraphicPokemon& pokemon : listOfGraphicsPokemon) {
				pokemon.walk(mRight, 1, 1);

			}
		counter++;



		app.setView(view);
		
		app.draw(player);
		statOfPlayer.drawStatistic(app, view.getCenter());
		

		app.display();
	}
	player.setPosition(140, 100);
}



