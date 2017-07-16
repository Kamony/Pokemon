#include "Player.h"
#include <iostream>


Player::Player()
{
	this->x = 10;
	this->y = 400;

	if( !texture_.loadFromFile("../Images/Human.png") )
	{
		std::cerr << "Texture was not loaded";
	}
	texture_.setSmooth(true);

	setTexture(texture_);
	setTextureRect(sf::IntRect(0, 0, 95, 158.75));
	scale(0.5, 0.5);
	
	
	surroundings.setSize(sf::Vector2f(101, 42));
	surroundings.scale(0.5, 0.5);
	surroundings.setFillColor(sf::Color::Green);

	setPosition(x, y);

	// texture battle
	if (!battleTexture.loadFromFile("../Images/playerTools/pokemonCatch.png"))
	{
		std::cerr << "texture not loaded";
	}
	battle.setTexture(battleTexture);
	battle.setTextureRect(sf::IntRect(0, 0, 128, 124));

}


Player::~Player()
{
}

void Player::walk(int direction, int mRight, int mx, int my)
{
	switch (direction)
	{
		//up
	case 1:
		y -= my;
		setTextureRect(sf::IntRect(mRight, 476.25, 95, 158.75));
		break;
	//down
	case 2:
		y += my;
		setTextureRect(sf::IntRect(mRight, 0, 95, 158.75));
		break;
	//left
	case 3:
		x -= mx;
		setTextureRect(sf::IntRect(mRight, 158.75, 95, 158.75));
		break;
	//right
	case 4:
		x += mx;
		setTextureRect(sf::IntRect(mRight, 317.5, 95, 158.75));
		break;
	}
	setPosition(x, y);
}

void Player::setPosition(float x, float y)
{
	Transformable::setPosition(x, y);
	surroundings.Transformable::setPosition(x - 3, y + 60);
}

sf::FloatRect Player::getSurroundings()
{
	return surroundings.getGlobalBounds();
}

void Player::catchPok(sf::RenderWindow& app, sf::Vector2f position)
{
	sf::Clock clock;
	float Frame = 0;
	float animSpeed = 0.15;
	int frameCount = 20;
	int mRight = 0;

	while (clock.getElapsedTime().asMilliseconds() < 2500)
	{
		//sprite animation of pokemon
		Frame += animSpeed;
		if (Frame > frameCount) Frame -= frameCount;
		mRight = int(Frame) * 128;
		if (mRight > 645) {
			mRight = 0;
			Frame = 0.3;
		}

		battle.setTextureRect(sf::IntRect(mRight, 0, 128, 124));

		battle.setPosition(position);
		battle.move(sf::Vector2f(-35, -55));
		app.clear();
		app.draw(battle);
		app.display();
	}
	
}


