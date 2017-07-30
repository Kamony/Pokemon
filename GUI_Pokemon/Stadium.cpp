#include "Stadium.h"
#include <iostream>
#include <SFML/Window/Event.hpp>
#include "FightAnime.h"


Stadium::Stadium(Player& player):/*Game(),*/player(player)
{
	if (!font.loadFromFile("../Fonts/arial.ttf"))
	{
		std::cerr << "font not loaded";
	}
	text.setFont(font);
	text.setString("YOU HAVE TO DEFEAT ME AND MY LEGENDARY POKEMONS!\nHAHAHAHA!!!");
	text.setFillColor(sf::Color::Red);
	victoryText.setFont(font);
	victoryText.setString("AAAARGH! YOU HAVE BESTED ME!\nI PASS TITLE OF CHAMPION TO YOU!");

	if (!champ_texture.loadFromFile("../Images/stadium/villain.png") ||
		bg_texture.loadFromFile("../Images/stadiumBG.png"))
		std::cerr << "texture not loaded";

	champ.setTexture(champ_texture);
	champ.setScale(0.3, 0.3);

	bg.setTexture(bg_texture);

	stadionBackEnd = Stadion();

	articuno = new GraphicPokemon(&stadionBackEnd.getVectorOfPokemon()[1], 300, 250);
	moltres = new GraphicPokemon(&stadionBackEnd.getVectorOfPokemon()[0], 500, 250);
	zapdos = new GraphicPokemon(&stadionBackEnd.getVectorOfPokemon()[2], 700, 250);

	art_alive = zap_alive = molt_alive = true;
}


Stadium::~Stadium()
{
}

void Stadium::draw(sf::RenderWindow& app)
{
	champ.setPosition(500, 100);
	text.setPosition(champ.getPosition() + sf::Vector2f(-250, -40));
	victoryText.setPosition(champ.getPosition() + sf::Vector2f(210, -200));

	
	float AFrame = 0;
	float ZFrame = 0;
	float MFrame = 0;
	float animSpeed = 0.3;
	int frameCount = 12;
	int CHmRight = 0;
	int mRightPlayer = 0;
	float FramePlayer = 0;
	float FrameChamp = 0;
	int  AmRight = 0;
	int  ZmRight = 0;
	int  MmRight = 0;

	player.setScale(0.8, 0.8);
	player.setPosition(550, 650);

	sf::Clock clock;

	while (app.isOpen())
	{
		sf::Event event;
		while (app.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				app.close();
			}
		}


		//sprite animation of champ
		FrameChamp += 0.1;
		CHmRight = int(FrameChamp) * 400;
		if (CHmRight > 1600) {
			CHmRight = 0;
			FrameChamp = 0.3;
		}
		champ.setTextureRect(sf::IntRect(CHmRight, 0, 400, 407));

		// animation of legendaries
		AFrame += animSpeed;
		ZFrame += animSpeed;
		MFrame += animSpeed;
		AmRight = int(AFrame) * 172;
		ZmRight = int(ZFrame) * 145;
		MmRight = int(MFrame) * 217;

		if (AmRight > 6708) {
			AmRight = 0;
			AFrame = 0.3;
		}

		if (ZmRight > 4196) {
			ZmRight = 0;
			ZFrame = 0.3;
		}

		if (MmRight > 9765) {
			MmRight = 0;
			MFrame = 0.3;
		}

		articuno->setTextureRect(sf::IntRect(AmRight, 0, 172, 171));
		zapdos->setTextureRect(sf::IntRect(ZmRight, 0, 145, 106));
		moltres->setTextureRect(sf::IntRect(MmRight, 0, 217, 181));

		//sprite animation of player
		FramePlayer += animSpeed;
		if (FramePlayer > frameCount) FramePlayer -= frameCount;
		mRightPlayer = int(FramePlayer) * 95;
		if (mRightPlayer > 950) {
			mRightPlayer = 0;
			FramePlayer = 0.3;
		}
//		movePlayer(player, mRightPlayer, 2, 2);

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		{
			if (Collide(player, *articuno))
			{
				std::cout << "ARTICUNO KOLIZE" << std::endl;
				GraphicPokemon* chosenFromPlayer = player.choosePokemon(app);
				if (chosenFromPlayer != nullptr)
				{
					FightAnime fight(player, *chosenFromPlayer, *articuno, app);
					if (fight.getResult())
					{
						art_alive = false;
					}
				}
			}

			if (Collide(player, *moltres))
			{
				std::cout << "MOLTRES KOLIZE" << std::endl;
				GraphicPokemon* chosenFromPlayer = player.choosePokemon(app);
				if (chosenFromPlayer != nullptr)
				{
					FightAnime fight(player, *chosenFromPlayer, *moltres, app);
					if (fight.getResult())
					{
						molt_alive = false;
					}
				}
			}

			if (Collide(player, *zapdos))
			{
				std::cout << "ZAPDOS KOLIZE" << std::endl;
				GraphicPokemon* chosenFromPlayer = player.choosePokemon(app);
				if (chosenFromPlayer != nullptr)
				{
					FightAnime fight(player, *chosenFromPlayer, *zapdos, app);
					if (fight.getResult())
					{
						zap_alive = false;
					}
				}
			}
		}
		
		app.clear();
		
		app.draw(bg);
		
		if (clock.getElapsedTime().asSeconds() < 5) app.draw(text);
		if (!(art_alive && zap_alive && molt_alive))
		{
			app.draw(victoryText);
		}
		app.draw(champ);
		
		if (art_alive) app.draw(*articuno);
		if (zap_alive) app.draw(*zapdos);
		if (molt_alive) app.draw(*moltres);
		
		app.draw(player);

		app.display();

	}
}
