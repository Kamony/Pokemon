#include "ResultAnime.h"
#include <iostream>
#include "Player.h"


ResultAnime::ResultAnime(std::string nameOfWinner, GraphicPokemon& loserPok, sf::RenderWindow& app, int stav)
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
	name.setPosition(winner.getPosition() + sf::Vector2f(10, 50));

	backButton.setFont(font);
	backButton.setFillColor(sf::Color::White);
	backButton.setString("PRESS 'B' TO GO BACK");
	backButton.setPosition(winner.getPosition() + sf::Vector2f(10, 50));

	resultOfCatch.setFont(font);
	
	switch (stav)
	{
	case 1:
		resultOfCatch.setFillColor(sf::Color::Green);
		resultOfCatch.setString("YOU WON THE BATTLE!");
		break;
	case 2:
		resultOfCatch.setFillColor(sf::Color::Green);
		resultOfCatch.setString("YOU WON THE BATTLE, ALTHOUGH IT WAS a TIE.");
		break;
	case 3:
		resultOfCatch.setFillColor(sf::Color::Red);
		resultOfCatch.setString("YOU LOST!");
		break;
	}
	resultOfCatch.setCharacterSize(80);
	resultOfCatch.setPosition(winner.getPosition() + sf::Vector2f(0, -30));
	//sprite and texture
	if (!pokeball_t.loadFromFile("../Images/playerTools/pokeball.png"))
	{
		std::cerr << "font not loaded";
	}
	pokeball.setTexture(pokeball_t);
	pokeball.setTextureRect(sf::IntRect(0, 0, 16, 13));
	
	loserPok.setScale(3, 3);
	pokeball.setScale(2, 2);

	time = sf::milliseconds(10);
	backNotPressed = true;

	draw(app, loserPok, stav);

}

ResultAnime::~ResultAnime()
{
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

	Player player;

	while (clock.getElapsedTime().asMilliseconds() < 5000)
	{
		app.clear();

		app.draw(resultOfCatch);
		app.draw(winner);

		if (++counter % 30 == 0)
		{
			name.setFillColor(sf::Color::White);
		}
		else
		{
			name.setFillColor(sf::Color::Green);
		}
		
		app.draw(name);
		app.display();
		
	}

	if (stav == 3)
	{
		backNotPressed = false;
	}

	clock.restart();
	

	while (backNotPressed)
	{
		app.clear();

		// dodelat umisteni backbuttonu, eventy a hazeni pokebalu po stisknuti space

		Frame += animSpeed;
		if (Frame > frameCount) Frame -= frameCount;
		mRight = int(Frame) * 16;
		if (mRight > 110) {
			mRight = 0;
			Frame = 0.3;
		}
		pokeball.setTextureRect(sf::IntRect(mRight, 0, 16, 13));
		pokeball.move(sf::Vector2f(0, 2));

		if (loser.getSurroundings().intersects(pokeball.getGlobalBounds()))
		{
			std::cout << "DOPAD";
			player.catchPok(app, loser.getPosition());
		}


		app.draw(pokeball);
		app.draw(loser);

		app.display();
	}
}
