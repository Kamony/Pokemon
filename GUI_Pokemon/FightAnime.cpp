#include "FightAnime.h"
#include <iostream>
#include <SFML/Window/Event.hpp>
#include <iomanip>
#include "ResultAnime.h"


void FightAnime::initGraphics()
{
	// textures
	if (!this->pokHealthBar.loadFromFile("../Images/playerTools/healthBar.png"))
	{
		std::cerr << "texture not loaded";
	}
	if (!this->hitTexture.loadFromFile("../Images/playerTools/punchs_01.png"))
	{
		std::cerr << "texture not loaded";
	}
	if (!this->battle_t.loadFromFile("../Images/playerTools/battle_01.png"))
	{
		std::cerr << "texture not loaded";
	}


	if (!bg_texture.loadFromFile("../Images/battleBG.png"))
	{
		std::cerr << "texture not loaded - Battle" << std::endl;
	}
	
	// sprites
	bg.setTexture(bg_texture);

	upperPok.setTexture(pokHealthBar);
	upperPok.setTextureRect(sf::IntRect(0, 0, 179, 32));
	healthUp.setTexture(pokHealthBar);
	healthUp.setTextureRect(sf::IntRect(13, 36, 175, 53));
	healthUp.setScale(1, 0.35);

	bottomPok.setTexture(pokHealthBar);
	bottomPok.setTextureRect(sf::IntRect(0, 0, 179, 32));
	healthBot.setTexture(pokHealthBar);
	healthBot.setTextureRect(sf::IntRect(13, 36, 175, 53));
	healthBot.setScale(1, 0.35);

	upperPok.setPosition(50, 80);
	bottomPok.setPosition(950, 700);
	healthUp.setPosition(upperPok.getPosition()+ sf::Vector2f(12, 6));
	
	healthBot.setPosition(bottomPok.getPosition()+ sf::Vector2f(12, 6));

	
	hit.setTexture(hitTexture);
	hit.setTextureRect(sf::IntRect(10, 17, 67, 69));

	battle.setTexture(battle_t);
	battle.setTextureRect(sf::IntRect(0, 0, 200, 150));
	battle.setPosition(300, 200);
	battle.setScale(3, 3);

	//texts
	if (!font.loadFromFile("../Fonts/arial.ttf"))
	{
		std::cerr << "font not loaded";
	}

	nameP1.setFont(font);
	nameP1.setString(gPok1->getPokemon().getJmeno());
	nameP1.setFillColor(sf::Color::White);
	nameP1.setPosition(upperPok.getPosition()+sf::Vector2f(0, -40));
	

	nameP2.setFont(font);
	nameP2.setString(gPok2->getPokemon().getJmeno());
	nameP2.setFillColor(sf::Color::White);
	nameP2.setPosition(bottomPok.getPosition()+sf::Vector2f(0, -40));

	damage.setFont(font);
	damage.setFillColor(sf::Color::White);

	Intro.setFont(font);
	Intro.setString("VERSUS");
	Intro.setFillColor(sf::Color::White);
}

FightAnime::FightAnime(Player& p,GraphicPokemon& pok1, GraphicPokemon& pok2, sf::RenderWindow& app):player(p)
{
	pokemonCaught = false;
	
	//hracuv pok
	gPok1 = &pok1;
	//nepritel
	gPok2 = &pok2;

	initGraphics();

	// set battle status of both pokemons
	souboj = new Arena(gPok1->getPokemon(), gPok2->getPokemon());

	gPok1->getPokemon().setForBattle(souboj->getUtokPok1(), souboj->getObranaPok1());
	gPok2->getPokemon().setForBattle(souboj->getUtokPok2(), souboj->getObranaPok2());
	
	std::string name = gPok2->getID();
	if (name != "Articuno" || name != "Moltres" || name != "Zapdos")
	{
		draw(app);
	}
	else drawForStadium(app);

	
	
}

FightAnime::~FightAnime()
{
}

float FightAnime::pok1Attack()
{
	float damage = gPok1->getPokemon().getUtok();
	gPok2->getPokemon().setHp(-damage);
	return damage;
}

float FightAnime::pok2Attack()
{
	float damage = gPok2->getPokemon().getUtok();
	gPok1->getPokemon().setHp(-damage);
	return damage;
}


void FightAnime::animateBattle(float animSpeed, int frameCount, float& FrameB, int mRightB)
{
	FrameB += animSpeed;
	if (FrameB > frameCount) FrameB -= frameCount;
	mRightB = int(FrameB) * 200;

	if (mRightB > 1800) {
		mRightB = 0;
		FrameB = 0.3;
	}

	battle.setTextureRect(sf::IntRect(mRightB, 0, 200, 150));
}

void FightAnime::animateIntroOfFight(sf::RenderWindow& app, sf::Clock clock)
{
	nameP2.setPosition(500,350);
	nameP2.setCharacterSize(40);
	nameP2.setFillColor(sf::Color::Red);
	
	//versus
	Intro.setPosition(510, 400);
	Intro.setOutlineColor(sf::Color::Black);
	Intro.setOutlineThickness(10);

	nameP1.setPosition(500,450);
	nameP1.setCharacterSize(40);
	nameP1.setFillColor(sf::Color::Green);

	while (clock.getElapsedTime().asSeconds() < 4)
	{
		nameP1.move(-1, -1);
		nameP2.move(1, 1);
		app.clear();
		app.draw(bg);
		app.draw(nameP1);
		app.draw(nameP2);
		app.draw(Intro);
		app.display();
	}
}

void FightAnime::draw(sf::RenderWindow& app)
{
	// start time measuring
	sf::Clock clock;

	float Frame = 0;
	float animSpeed = 0.2;
	int frameCount = 20;
	int mRight = 0;
	bool animeActive = false;
	float damageHolder = 0;
	int counter = 0;
	int mRightBatlle = 0;
	float FrameB = 0;
	int mRightB = 0;

	animateIntroOfFight(app, clock);

	clock.restart();
	
	nameP2.setPosition(bottomPok.getPosition() + sf::Vector2f(0, -40));
	nameP1.setPosition(upperPok.getPosition() + sf::Vector2f(0, -40));
	
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

	
		animateBattle(animSpeed-0.05, frameCount, FrameB, mRightB);
				
		// every second do iteration
		sf::Int32 msec = clock.getElapsedTime().asMilliseconds();
		if( msec % 1000 <= 100 )
		{
			if (gPok1->getPokemon().getHp()<=0 && gPok2->getPokemon().getHp()<=0)
			{
				// victory screen + attempt to catch pokemon +  go back to wilderness
				std::cout << "KONEC BOJE REMIZA";
				ResultAnime result(player, gPok1->getPokemon().getJmeno(), *gPok2, app, 2);
				pokemonCaught = result.getResult();
				break;
			}
			else
			{
				if (gPok1->getPokemon().getHp()<=0 && gPok2->getPokemon().getHp()>0)
				{
					std::cout << "KONEC BOJE PROHRA";
					ResultAnime result(player, gPok2->getPokemon().getJmeno(), *gPok1, app, 3);
					pokemonCaught = result.getResult();
					break;
				}
				else
				{
					if (gPok1->getPokemon().getHp()>0 && gPok2->getPokemon().getHp()<=0)
					{
						std::cout << "KONEC BOJE VYHRA";
						ResultAnime result(player, gPok1->getPokemon().getJmeno(), *gPok2, app, 1);
						pokemonCaught = result.getResult();
						break;
					}
				}
				counter++;
				damageHolder = pok1Attack();
	
				damage.setString("-"+std::to_string(damageHolder));
				animeActive = true;
				while (animeActive)
				{
					//sprite animation of pokemon
					Frame += animSpeed;
					
					if (Frame > frameCount) Frame -= frameCount;
					mRight = int(Frame) * 83;
					if (mRight > 300) {
						mRight = 0;
						Frame = 0.3;
						animeActive = false;
					}
					
					animateBattle(animSpeed - 0.05, frameCount, FrameB, mRightB);
					
					hit.setTextureRect(sf::IntRect(mRight, 17, 67, 69));
					hit.setPosition(bottomPok.getPosition());
					damage.setPosition(hit.getPosition());
					damage.move(sf::Vector2f(10, 10));
					int newc = 175 - (counter*damageHolder*1.75);
					healthBot.setTextureRect(sf::IntRect(13, 36, newc, 53));
					
					app.clear();

					app.draw(bg);
					app.draw(nameP1);
					app.draw(nameP2);
					app.draw(healthUp);
					app.draw(healthBot);
					app.draw(upperPok);
					app.draw(bottomPok);
					app.draw(hit);
					app.draw(damage);
					app.draw(battle);
					app.display();
					
				}
				damageHolder = pok2Attack();
				damage.setString("-" + std::to_string(damageHolder));
				animeActive = true;
				while (animeActive)
				{
					//sprite animation of pokemon
					Frame += animSpeed;
					
					if (Frame > frameCount) Frame -= frameCount;
					mRight = int(Frame) * 83;
					
					if (mRight > 300) {
						mRight = 0;
						Frame = 0.3;
						animeActive = false;
					}
					
					animateBattle(animSpeed - 0.05, frameCount, FrameB, mRightB);

					hit.setTextureRect(sf::IntRect(mRight, 17, 67, 69));
					hit.setPosition(upperPok.getPosition());
					damage.setPosition(hit.getPosition());
					damage.move(sf::Vector2f(10, 10));
					int newc = 175 - (counter*damageHolder*1.75);
					healthUp.setTextureRect(sf::IntRect(13, 36, newc, 53));
					
					app.clear();

					app.draw(bg);
					app.draw(nameP1);
					app.draw(nameP2);
					app.draw(healthUp);
					app.draw(healthBot);
					app.draw(upperPok);
					app.draw(bottomPok);
					app.draw(hit);
					app.draw(damage);
					app.draw(battle);

					app.display();
				}
			}
		}



		app.clear();
		app.draw(bg);
		app.draw(nameP1);
		app.draw(nameP2);
		app.draw(healthUp);
		app.draw(healthBot);
		app.draw(upperPok);
		app.draw(bottomPok);
		app.draw(battle);

		app.display();

	}
	
}

void FightAnime::drawForStadium(sf::RenderWindow& app)
{
	// start time measuring
	sf::Clock clock;

	float Frame = 0;
	float animSpeed = 0.2;
	int frameCount = 20;
	int mRight = 0;
	bool animeActive = false;
	float damageHolder = 0;
	int counter = 0;
	int mRightBatlle = 0;
	float FrameB = 0;
	int mRightB = 0;

	animateIntroOfFight(app, clock);

	clock.restart();

	nameP2.setPosition(bottomPok.getPosition() + sf::Vector2f(0, -40));
	nameP1.setPosition(upperPok.getPosition() + sf::Vector2f(0, -40));

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


		animateBattle(animSpeed - 0.05, frameCount, FrameB, mRightB);

		// every second do iteration
		sf::Int32 msec = clock.getElapsedTime().asMilliseconds();
		if (msec % 1000 <= 100)
		{
			if (gPok1->getPokemon().getHp() <= 0 && gPok2->getPokemon().getHp() <= 0)
			{
				std::cout << "KONEC BOJE REMIZA";
				ResultAnime result(player, app, 2);
				break;
			}
			else
			{
				if (gPok1->getPokemon().getHp() <= 0 && gPok2->getPokemon().getHp()>0)
				{
					std::cout << "KONEC BOJE PROHRA";
					ResultAnime result(player, app, 3);
					break;
				}
				else
				{
					if (gPok1->getPokemon().getHp()>0 && gPok2->getPokemon().getHp() <= 0)
					{
						std::cout << "KONEC BOJE VYHRA";
						ResultAnime result(player, app, 1);
						break;
					}
				}
				counter++;
				damageHolder = pok1Attack();

				damage.setString("-" + std::to_string(damageHolder));
				animeActive = true;
				while (animeActive)
				{
					//sprite animation of pokemon
					Frame += animSpeed;

					if (Frame > frameCount) Frame -= frameCount;
					mRight = int(Frame) * 83;
					if (mRight > 300) {
						mRight = 0;
						Frame = 0.3;
						animeActive = false;
					}

					animateBattle(animSpeed - 0.05, frameCount, FrameB, mRightB);

					hit.setTextureRect(sf::IntRect(mRight, 17, 67, 69));
					hit.setPosition(bottomPok.getPosition());
					damage.setPosition(hit.getPosition());
					damage.move(sf::Vector2f(10, 10));
					int newc = 175 - (counter*damageHolder*1.75);
					healthBot.setTextureRect(sf::IntRect(13, 36, newc, 53));

					app.clear();

					app.draw(bg);
					app.draw(nameP1);
					app.draw(nameP2);
					app.draw(healthUp);
					app.draw(healthBot);
					app.draw(upperPok);
					app.draw(bottomPok);
					app.draw(hit);
					app.draw(damage);
					app.draw(battle);
					app.display();

				}
				damageHolder = pok2Attack();
				damage.setString("-" + std::to_string(damageHolder));
				animeActive = true;
				while (animeActive)
				{
					//sprite animation of pokemon
					Frame += animSpeed;

					if (Frame > frameCount) Frame -= frameCount;
					mRight = int(Frame) * 83;

					if (mRight > 300) {
						mRight = 0;
						Frame = 0.3;
						animeActive = false;
					}

					animateBattle(animSpeed - 0.05, frameCount, FrameB, mRightB);

					hit.setTextureRect(sf::IntRect(mRight, 17, 67, 69));
					hit.setPosition(upperPok.getPosition());
					damage.setPosition(hit.getPosition());
					damage.move(sf::Vector2f(10, 10));
					int newc = 175 - (counter*damageHolder*1.75);
					healthUp.setTextureRect(sf::IntRect(13, 36, newc, 53));

					app.clear();

					app.draw(bg);
					app.draw(nameP1);
					app.draw(nameP2);
					app.draw(healthUp);
					app.draw(healthBot);
					app.draw(upperPok);
					app.draw(bottomPok);
					app.draw(hit);
					app.draw(damage);
					app.draw(battle);

					app.display();
				}
			}
		}



		app.clear();
		app.draw(bg);
		app.draw(nameP1);
		app.draw(nameP2);
		app.draw(healthUp);
		app.draw(healthBot);
		app.draw(upperPok);
		app.draw(bottomPok);
		app.draw(battle);

		app.display();

	}
}


