#pragma once
#include <SFML/Graphics/Text.hpp>

class MenuGeneric
{
protected:
	int selectedItemId;
	sf::Font font;
	std::vector<sf::Text> menu;
public:
	MenuGeneric();
	~MenuGeneric();

	virtual void moveUp();
	virtual void moveDown();
	virtual int getPressedItem() const;
};

