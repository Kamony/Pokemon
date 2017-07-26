#pragma once
#include "../../Pokemon/Pokemon/Batoh.h"
#include "../../Pokemon/Pokemon/Trener.h"
#include "SFML/Graphics.hpp"

#include <string>
#include "MenuGeneric.h"
#include "Player.h"


class BackPack: public MenuGeneric
{
private:
	Trener *trener;
		
	sf::Texture tItems;
	sf::Sprite sItems;
		
	float w, h;
	Player* player;
	std::vector<sf::Text> items;
public:
	BackPack();
	BackPack(float width, float height, Player& player, Trener* trener);
	~BackPack();

	void draw(sf::RenderWindow &window);
	
};

