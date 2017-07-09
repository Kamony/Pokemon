#include "Wilderness.h"
#include <iostream>

Wilderness::Wilderness(float w, float h) :Game(), W(w), H(h)
{
	rng();
	
	texture_.loadFromFile("../Images/wilderness.jpg");
	sprite_.setTexture(texture_);
	sprite_.setTextureRect(sf::IntRect(0,0,W,H));
	
	this->divocina = new Divocina();
	for (Pokemon& pokemon : divocina->getVectorOfPokemon())
	{
		GraphicPokemon* item = new GraphicPokemon(&pokemon,rng);
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
	float animSpeed = 0.000001;
	int frameCount = 20;
	int mRight = 0;

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

		//sprite animation
		Frame += animSpeed;
		if (Frame>frameCount) Frame -= frameCount;
		mRight = int(Frame) * 32;
		if (mRight > 70) {
			mRight = 0;
			Frame = 0.3;
		}

		for (GraphicPokemon& pokemon : listOfGraphicsPokemon) {
			pokemon.randomWalk(mRight, 3, 3);
		
		}
		movePlayer(sPlayer, x, y, mRight, 3, 3);
			
		// set coordinates of sprites in main
		sPlayer.setPosition(50, 50);
		sprite_.setPosition(0, 0);
		//draw
		app.clear();
		//app.draw(sprite_);
		app.draw(sPlayer);
		for (GraphicPokemon& pokemon : listOfGraphicsPokemon)
		{
			pokemon.setPosition(pokemon.getX(),pokemon.getY());
			app.draw(pokemon);
		}
		app.display();
	}

}

