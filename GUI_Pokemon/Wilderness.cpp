#include "Wilderness.h"
#include <iostream>

Wilderness::Wilderness(float w, float h) :Game(), W(w), H(h)
{
	rng();
	
	// distributions that maps random coordinates 
	std::uniform_int_distribution<> randomXcoordinate(1, 1200);
	std::uniform_int_distribution<> randomYcoordinate(1, 800);
	

	texture_.loadFromFile("../Images/wilderness.jpg");
	sprite_.setTexture(texture_);
	sprite_.setTextureRect(sf::IntRect(0,0,W,H));
	
	this->divocina = new Divocina();
	for (Pokemon& pokemon : divocina->getVectorOfPokemon())
	{
		GraphicPokemon* item = new GraphicPokemon(&pokemon, randomXcoordinate(rng), randomYcoordinate(rng));
		listOfGraphicsPokemon.push_back(*item);
		
	}
}

Wilderness::~Wilderness()
{
}

void Wilderness::draw(sf::RenderWindow& app)
{
	float x = 300, y = 300;
	float Frame = 0;
	float animSpeed = 0.15;
	int frameCount = 20;
	int mRight = 0;
	int mRightPlayer = 0;
	float FramePlayer = 0;
	int counter = 0;
	
	Player player;
	// distribution that maps 1 - 5
	std::uniform_int_distribution<> five(1, 5);

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
		}

		//sprite animation of pokemon
		Frame += animSpeed;
		if (Frame>frameCount) Frame -= frameCount;
		mRight = int(Frame) * 32;
		if (mRight > 70) {
			mRight = 0;
			Frame = 0.3;
		}

		//sprite animation of player
		FramePlayer += animSpeed;
		if (FramePlayer>frameCount) FramePlayer -= frameCount;
		mRightPlayer = int(FramePlayer) * 95;
		if (mRightPlayer > 950) {
			mRightPlayer = 0;
			FramePlayer = 0.3;
		}

		if (counter % 20 == 0)
		{
			for (GraphicPokemon& pokemon : listOfGraphicsPokemon) {
				pokemon.randomWalk(mRight, 1, 1, five(rng));
				
			}
		} else
			for (GraphicPokemon& pokemon : listOfGraphicsPokemon) {
				pokemon.walk(mRight, 1, 1);
				
			}
		counter++;
		
		Game::movePlayer(player, mRightPlayer, 2, 2);

		// set coordinates of sprites in main
		
		sprite_.setPosition(0, 0);
		//draw
		app.clear();
		//app.draw(sprite_);
		

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
						oPokemon.checkForNeighbours(mRight, 2,2);
						pokemon.checkForNeighbours(mRight, 2, 2);
					}
				}
			}
			app.draw(pokemon);
		}
		app.draw(player.getCollideArea());
		app.draw(player);
		app.display();
	}

}

