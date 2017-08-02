#include "Stadium.h"
#include <iostream>
#include <SFML/Window/Event.hpp>
#include "FightAnime.h"


Stadium::Stadium(Player& player):player(player)
{
	if (!font.loadFromFile("../Fonts/arial.ttf"))
	{
		std::cerr << "font not loaded";
	}
	text.setFont(font);
	text.setString("YOU HAVE TO DEFEAT ME AND MY LEGENDARY POKEMONS!\nHAHAHAHA!!!");
	text.setFillColor(sf::Color::Red);
	text.setOutlineColor(sf::Color(157, 175, 192));
	text.setOutlineThickness(16);

	victoryText.setFont(font);
	victoryText.setString("AAAARGH! YOU HAVE BESTED ME!\nI PASS TITLE OF THE CHAMPION TO YOU!");
	victoryText.setFillColor(sf::Color::Red);
	victoryText.setOutlineColor(sf::Color(157,175,192));
	victoryText.setOutlineThickness(16);

	if (!champ_texture.loadFromFile("../Images/stadium/villain.png") ||
		!bg_texture.loadFromFile("../Images/stadiumBG.png") ||
		!crown_texture.loadFromFile("../Images/stadium/crown.png"))
		std::cerr << "texture not loaded - STADIUM" << std::endl;

	champ.setTexture(champ_texture);
	champ.setScale(0.3, 0.3);

	bg.setTexture(bg_texture);
	crown.setTexture(crown_texture);
	crown.setPosition(573, 350);
	crown.setScale(2,2);

	movingArea = sf::FloatRect(95, 90, 1007, 628);
	exit = sf::FloatRect(454, 732, 274, 71);
	stadionBackEnd = Stadion();

	articuno = new GraphicPokemon(&stadionBackEnd.getVectorOfPokemon()[1], 300, 250);
	moltres = new GraphicPokemon(&stadionBackEnd.getVectorOfPokemon()[0], 500, 250);
	zapdos = new GraphicPokemon(&stadionBackEnd.getVectorOfPokemon()[2], 700, 250);

	art_alive = zap_alive = molt_alive = true;
}


Stadium::~Stadium()
{
}

void Stadium::disablePokemon(GraphicPokemon& pok)
{
	pok.setScale(0.001, 0.001);
	pok.setX(0);
	pok.setY(0);
}
void Stadium::drawEndOfGame(sf::RenderWindow& app)
{
	bool end = true;

	sf::Text endText("That's all Folks!\nThank you for playing.\nI hope you enjoyed the game\n\nJiri Hauser\n2017\n\n\n\nPress 'B' to exit", font, 30);
	endText.setPosition(200, 200);
	endText.setFillColor(sf::Color::White);

	while (end)
	{
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
					app.close();
				}
			}
		}
		
		app.clear();
		app.draw(endText);
		app.display();
	}
}

void Stadium::drawAfterVictory(sf::RenderWindow& app,float& FrameCrown, int& CmRight)
{
		//sprite animation of champ
		FrameCrown += 0.1;
		CmRight = int(FrameCrown) * 25;
		if (CmRight > 475) {
			CmRight = 0;
			FrameCrown = 0.3;
		}
		crown.setTextureRect(sf::IntRect(CmRight, 0, 25, 27));

		if (Collide(player,crown))
		{
			drawEndOfGame(app);
		}
	
	app.draw(crown);
}

void Stadium::draw(sf::RenderWindow& app)
{
	champ.setPosition(500, 100);
	text.setPosition(champ.getPosition() + sf::Vector2f(-250, -40));
	victoryText.setPosition(champ.getPosition() + sf::Vector2f(-250, -55));


	float AFrame = 0;
	float ZFrame = 0;
	float MFrame = 0;
	float animSpeed = 0.3;
	int frameCount = 12;

	float FramePlayer = 0;
	float FrameChamp = 0;
	
	int	CHmRight = 0;
	int	mRightPlayer = 0;
	int AmRight = 0;
	int ZmRight = 0;
	int MmRight = 0;


	float FrameCrown = 0;
	int CmRight = 0;
	int lastMovP = 0;


	////test
	//zap_alive = false;
	//art_alive = false;
	////konec tetsu

	int lastDirectionOfMovement = 0;


	player.setScale(0.6, 0.6);
	player.setPosition(555, 610);

	bool exitNotPressed = true;

	sf::Clock clock;

	
	while (exitNotPressed)
	{
		sf::Event event;
		while (app.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				app.close();
			}
			if (event.type == sf::Event::KeyPressed)
			{
				switch (event.key.code)
				{
				case sf::Keyboard::I:
				{
					std::cout << "BATOH" << std::endl;
					BackPack batoh = BackPack(1200, 800, player, player.getBackEndTrener());

					batoh.draw(app);
					break;
				}
				case sf::Keyboard::S:
				{
					std::cout << "SHOP" << std::endl;

					Store store(player);
					store.draw(app);
					break;
				}
				default:
					break;
				}
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
		handlePlayerMovement(player, lastDirectionOfMovement, mRightPlayer, movingArea);

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		{
			if (Collide(player, *articuno))
			{
				std::cout << "ARTICUNO KOLIZE" << std::endl;
				GraphicPokemon* chosenFromPlayer = player.choosePokemon(app);
				if (chosenFromPlayer != nullptr)
				{
					FightAnime fight(player, *chosenFromPlayer, *articuno, app);
					if (articuno->getPokemon().getHp() <= 0)
					{
						art_alive = false;
						disablePokemon(*articuno);
						player.setPosition(555, 610);
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
					if (moltres->getPokemon().getHp() <= 0)
					{
						molt_alive = false;
						disablePokemon(*moltres);
						player.setPosition(555, 610);
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
					if (zapdos->getPokemon().getHp() <= 0)
					{
						zap_alive = false;
						disablePokemon(*zapdos);
						player.setPosition(555, 610);
					}
				}
			}
		}

		if (exit.intersects(player.getGlobalBounds()))
		{
			exitNotPressed = false;
		}

		app.clear();
		
		app.draw(bg);
		
		if (clock.getElapsedTime().asSeconds() < 5) app.draw(text);
		if (art_alive == false && zap_alive == false && molt_alive == false)
		{
			app.draw(victoryText);
			drawAfterVictory(app,FrameCrown,CmRight);
		}
		app.draw(champ);
		
		if (art_alive) app.draw(*articuno);
		if (zap_alive) app.draw(*zapdos);
		if (molt_alive) app.draw(*moltres);
		
		app.draw(player);
		
		app.display();

	}
	player.setPosition(630, 100);
	player.setScale(0.3, 0.3);
}
