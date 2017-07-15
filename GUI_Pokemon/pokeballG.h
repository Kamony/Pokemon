#pragma once
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

class pokeballG: public sf::Sprite
{
	sf::Texture texture_;
	float x, y;
	float initX, initY;
	bool isThrown;
public:
	pokeballG();
	~pokeballG();

	void setInitPosition(sf::Vector2f position);

	bool getState()
	{
		return isThrown;
	}

	void isTrown()
	{
		isThrown = true;
	}

	void isNotTrown()
	{
		isThrown = false;
	}

	float getYThrowCoordinate();

	void reset()
	{
		x = 0; y = 0; isThrown = false;
	}

	float getX()
	{
		x += 1;
		return x;
	}
};

