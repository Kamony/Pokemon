#include "PreGame.h"
#include <iostream>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Event.hpp>


PreGame::PreGame()
{
	
	if (!font.loadFromFile("../Fonts/arial.ttf"))
	{
		std::cerr << "font not loaded";
	}

	intro.setFont(font);
	intro.setCharacterSize(25);
	intro.setOutlineColor(sf::Color::Black);
	intro.setOutlineThickness(3);
	intro.setString("Welcome trainer, you are about to go to a journey to the world of POKEMON.\nBefore you proceed, choose one pokemon below to help you on your journey.\nChoose wisely,\neach pokemon is of some type and is strong against different enemies,\njust like in real world, where water is stronger than fire.\nTo win you have to defeat local champion of the gym, but his pokemons are strong,\nso you should first go into the wild to catch some reinforcements.");
	intro.setPosition(145, 50);

	enterButton.setFont(font);
	enterButton.setString("PRESS 'Space' TO CHOOSE");
	enterButton.setPosition(400, 700);

	if (!oakT.loadFromFile("../Images/playerTools/oak.png"))
	{
		std::cerr << "texture error";
	}

	oak.setTexture(oakT);
	oak.setPosition(5, 5);

	if (!bg_texture.loadFromFile("../Images/catchBG.png"))
	{
		std::cerr << "texture not loaded - Battle" << std::endl;
	}

	// sprites
	bg.setTexture(bg_texture);


	if (!bulbT.loadFromFile("../Images/pokemons/bulbasaur.png"))
	{
		std::cerr << "texture error";
	}
	bulbasaur.setTexture(bulbT);

	
	if (!charT.loadFromFile("../Images/pokemons/charmander.png"))
	{
		std::cerr << "texture error";
	}
	charmander.setTexture(charT);

	
	if (!squirT.loadFromFile("../Images/pokemons/squirtle.png"))
	{
		std::cerr << "texture error";
	}
	squirtle.setTexture(squirT);

	bulbasaur.setPosition(intro.getPosition() + sf::Vector2f(150, 300));
	charmander.setPosition(bulbasaur.getPosition() + sf::Vector2f(200, 0));
	squirtle.setPosition(charmander.getPosition() + sf::Vector2f(200, 0));

	area.setSize(sf::Vector2f(200, 200));
	area.setFillColor(sf::Color::Transparent);
	area.setOutlineThickness(10);
	area.setOutlineColor(sf::Color::Green);
	area.setOrigin(10, 10);
	area.setPosition(bulbasaur.getPosition());

	chosenPok = 1;
}



PreGame::~PreGame()
{
}

void PreGame::draw(sf::RenderWindow& app)
{
	float Frame = 0;
	float animSpeed = 0.3;
	int frameCount = 67;
	
	int  BmRight = 0;
	int  CHmRight = 0;
	int  SmRight = 0;

	bool spaceNotPressed = true;

	while (spaceNotPressed)
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
				if (event.key.code == sf::Keyboard::Right)
				{
					if (chosenPok != 3)
					{
						area.move(sf::Vector2f(200, 0));
					}
					
					if (++chosenPok>3)
					{
						chosenPok = 3;
					}
				}
				if (event.key.code == sf::Keyboard::Left)
				{
					if (chosenPok != 1)
					{
						area.move(sf::Vector2f(-200, 0));
					}
					
					if (--chosenPok<1)
					{
						chosenPok = 1;
					}
				}
				if (event.key.code == sf::Keyboard::Space)
				{
					spaceNotPressed = false;
				}
			}
		}

		

		Frame += animSpeed;
		if (Frame > frameCount) Frame -= frameCount;
		BmRight = int(Frame) * 192;
		CHmRight = int(Frame) * 192;
		SmRight = int(Frame) * 192;
		
		if (BmRight > 9600) {
			BmRight = 0;
			Frame = 0.3;
		}

		if (CHmRight > 12864) {
			CHmRight = 0;
			Frame = 0.3;
		}

		if (SmRight > 12480) {
			SmRight = 0;
			Frame = 0.3;
		}
		
		bulbasaur.setTextureRect(sf::IntRect(BmRight, 0, 192, 192));
		charmander.setTextureRect(sf::IntRect(CHmRight, 0, 192, 192));
		squirtle.setTextureRect(sf::IntRect(SmRight, 0, 192, 192));

		app.clear();
		
		app.draw(bg);
		app.draw(oak);
		app.draw(intro);
		app.draw(area);
		app.draw(bulbasaur);
		app.draw(charmander);
		app.draw(squirtle);
		app.draw(enterButton);
		app.display();

	}


}
