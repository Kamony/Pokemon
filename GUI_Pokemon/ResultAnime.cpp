#include "ResultAnime.h"
#include <iostream>
#include "Player.h"
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Event.hpp>


void ResultAnime::initResult(int stav)
{
	resultOfCatch.setFont(font);
	
	switch (stav)
	{
	case 1:
		resultOfCatch.setFillColor(sf::Color::Green);
		resultOfCatch.setString("YOU WON THE BATTLE!");
		break;
	case 2:
		resultOfCatch.setFillColor(sf::Color::Green);
		resultOfCatch.setString("IT WAS a TIE.");
		break;
	case 3:
		resultOfCatch.setFillColor(sf::Color::Red);
		resultOfCatch.setString("YOU LOST!");
		break;
	}
	resultOfCatch.setCharacterSize(65);
}

ResultAnime::ResultAnime(Player& player,std::string nameOfWinner, GraphicPokemon& loserPok, sf::RenderWindow& app, int stav):player(player)
{
	if (!font.loadFromFile("../Fonts/arial.ttf"))
	{
		std::cerr << "font not loaded";
	}

	winner.setFont(font);
	winner.setFillColor(sf::Color::White);
	winner.setCharacterSize(40);
	winner.setString("WINNER IS");
	winner.setPosition(400, 300);

	name.setFont(font);
	name.setFillColor(sf::Color::Green);
	name.setCharacterSize(60);
	name.setString(nameOfWinner);
	name.setPosition(winner.getPosition() + sf::Vector2f(5, 50));

	backButton.setFont(font);
	backButton.setFillColor(sf::Color::White);
	backButton.setString("PRESS 'B' TO GO BACK");
	backButton.setPosition(500,750);

	actionButton.setFont(font);
	actionButton.setFillColor(sf::Color::White);
	actionButton.setString("PRESS 'Space' TO THROW POKEBAL ");
	actionButton.setPosition(5,10);

	continueText.setFont(font);
	continueText.setFillColor(sf::Color::White);
	continueText.setString("PRESS 'Space' TO TRY CATCH THE POKEMON ");
	continueText.setPosition(5, 10);
	initResult(stav);
	resultOfCatch.setPosition(winner.getPosition() + sf::Vector2f(0, -80));
	//sprite and texture
	if (!pokeball_t.loadFromFile("../Images/playerTools/pokeball.png"))
	{
		std::cerr << "font not loaded";
	}
	pokeball.setTexture(pokeball_t);
	pokeball.setTextureRect(sf::IntRect(0, 0, 16, 13));
	
	loserPok.setScale(3, 3);
	pokeball.setScale(2, 2);

	backNotPressed = true;

	draw(app, loserPok, stav);

}

ResultAnime::ResultAnime(Player& player, sf::RenderWindow& app, int stav) :player(player)
{
	if (!font.loadFromFile("../Fonts/arial.ttf"))
	{
		std::cerr << "font not loaded";
	}

	initResult(stav);

	backButton.setFont(font);
	backButton.setFillColor(sf::Color::White);
	backButton.setString("PRESS 'B' TO CONTINUE");
	backButton.setPosition(500, 750);

	backNotPressed = true;
}


ResultAnime::~ResultAnime()
{
}

void ResultAnime::animateResult(sf::RenderWindow& app, int stav, int counter, bool choice)
{
	while (choice)
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
				if (event.key.code == sf::Keyboard::Space)
				{
					std::cout << "Pokracovani na hod";
					choice = false;
				}
				if (event.key.code == sf::Keyboard::B)
				{
					std::cout << "Zpet";
					choice = false;
					backNotPressed = false;
				}
			}
		}

		app.clear();

		if (stav != 3)
		{
			app.draw(continueText);
			if (++counter % 30 == 0)
			{
				name.setFillColor(sf::Color::Green);
			}
		}
		else
		{
			backNotPressed = false;
			if (++counter % 30 == 0)
			{
				name.setFillColor(sf::Color::Red);
			}
		}

		

		app.draw(resultOfCatch);
		app.draw(winner);
		app.draw(name);
		app.draw(backButton);
		app.display();
		
	}
}




void ResultAnime::draw(sf::RenderWindow& app, GraphicPokemon& loser, int stav)
{
	sf::Clock clock;
	int counter = 0;

	loser.setPosition(550, 350);
	loser.setX(550);
	loser.setY(350);
	pokeball.setPosition(loser.getPosition()+sf::Vector2f(10,-300));

	float Frame = 0;
	float animSpeed = 0.2;
	int frameCount = 20;
	int mRight = 0;

	
	bool choice = true;
	animateResult(app, stav, counter, choice);

	

	clock.restart();
	bool spacePressed = false;

	while (backNotPressed)
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
				if (event.key.code == sf::Keyboard::Space)
				{
					std::cout << "Hod";
					spacePressed = true;
				}
				if (event.key.code == sf::Keyboard::B)
				{
					std::cout << "Zpet";
					backNotPressed = false;
				}
			}
		}
		
		
		app.clear();

		if (spacePressed)
		{
			Frame += animSpeed;
			if (Frame > frameCount) Frame -= frameCount;
			mRight = int(Frame) * 16;
			if (mRight > 110) {
				mRight = 0;
				Frame = 0.3;
			}
			pokeball.setTextureRect(sf::IntRect(mRight, 0, 16, 13));
			pokeball.move(sf::Vector2f(0, 2));
		}

		if (loser.getSurroundings().intersects(pokeball.getGlobalBounds()))
		{
			std::cout << "DOPAD";
			pokemonCaught = player.catchPok(app, loser.getPosition(), loser.getPokemon());
			break;
		}

		app.draw(actionButton);
		app.draw(backButton);
		app.draw(pokeball);
		app.draw(loser);

		app.display();
	}
}

void ResultAnime::drawOnlyResult(sf::RenderWindow& app)
{
	
	while (backNotPressed)
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
				if (event.key.code == sf::Keyboard::B)
				{
					std::cout << "Zpet";
					backNotPressed = false;
				}
			}
		}
		app.clear();

		app.draw(resultOfCatch);
		app.draw(backButton);
		app.display();

	}
}
