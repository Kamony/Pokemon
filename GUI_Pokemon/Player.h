#pragma once
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

class Player: public sf::Sprite
{
private:
	//texture
	sf::Texture texture_;
	// position coordinates
	float x, y;
	sf::RectangleShape surroundings;
public:
	Player();
	~Player();

	/**
	 * \brief move player to position
	 * \param mRight changing upper left x coordinate
	 * \param mx shift of x coordinate
	 * \param my shift of y coordinate
	 * \param direction 1-up 2-down 3-left 4-right
	 */
	void walk(int direction, int mRight, int mx, int my);
	/**
	 * \brief sets position of Player and his surrounding area
	 * \param x x coordinate
	 * \param y y coordinate
	 */
	void setPosition(float x, float y);
	/**
	 * \brief Get surrounding area of Player
	 * \return GlobalBounds()
	 */
	sf::FloatRect getSurroundings();

	/**
	 * \brief get rectangle shaped surroundings
	 * \return surroundings
	 */
	sf::RectangleShape getCollideArea()
	{
		return surroundings;
	}
};

