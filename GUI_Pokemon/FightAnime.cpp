#include "FightAnime.h"
#include <iostream>
#include <SFML/Window/Event.hpp>
#include <iomanip>

FightAnime::FightAnime(GraphicPokemon& pok1, GraphicPokemon& pok2)
{
	// backend atributes
	pokemon1 = pok1.getPokemon();
	pokemon2 = pok2.getPokemon();

	// textures
	if (!this->pokHealthBar.loadFromFile("../Images/playerTools/healthBar.png"))
	{
		std::cerr << "texture not loaded";
	}
	if (!this->hitTexture.loadFromFile("../Images/playerTools/punchs_01.png"))
	{
		std::cerr << "texture not loaded";
	}
	// sprites
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

	upperPok.setPosition(30, 50);
	bottomPok.setPosition(900, 600);
	healthUp.setPosition(upperPok.getPosition()+ sf::Vector2f(12, 6));
	
	healthBot.setPosition(bottomPok.getPosition()+ sf::Vector2f(12, 6));

	
	hit.setTexture(hitTexture);
	hit.setTextureRect(sf::IntRect(10, 17, 67, 69));

	//texts
	if (!font.loadFromFile("../Fonts/arial.ttf"))
	{
		std::cerr << "font not loaded";
	}

	nameP1.setFont(font);
	nameP1.setString(pokemon1.getJmeno());
	nameP1.setFillColor(sf::Color::White);
	nameP1.setPosition(upperPok.getPosition()+sf::Vector2f(0, -40));
	//nameP1.move(sf::Vector2f(0, 15));

	nameP2.setFont(font);
	nameP2.setString(pokemon2.getJmeno());
	nameP2.setFillColor(sf::Color::White);
	nameP2.setPosition(bottomPok.getPosition()+sf::Vector2f(0, -40));
	//nameP2.move(sf::Vector2f(0, 15));

	damage.setFont(font);
	damage.setFillColor(sf::Color::White);

	// set battle status of both pokemons
	souboj = new Arena(pokemon1, pokemon2);

	pokemon1.setForBattle(souboj->getUtokPok1(), souboj->getObranaPok1());
	pokemon2.setForBattle(souboj->getUtokPok2(), souboj->getObranaPok2());

	// time init in ms
	time = sf::milliseconds(10);
	
}

FightAnime::~FightAnime()
{
}

float FightAnime::pok1Attack()
{
	float damage = pokemon1.getUtok();
	pokemon2.setHp(-damage);
	return damage;
}

float FightAnime::pok2Attack()
{
	float damage = pokemon2.getUtok();
	pokemon1.setHp(-damage);
	return damage;
}

void FightAnime::draw(sf::RenderWindow& app)
{
	// start time measuring
	sf::Clock clock;

	float Frame = 0;
	float animSpeed = 0.15;
	int frameCount = 20;
	int mRight = 0;
	bool animeActive = false;
	float damageHolder = 0;
	int counter = 0;

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
		// every second do iteration
		sf::Int32 msec = clock.getElapsedTime().asMilliseconds();
		if( msec % 1000 <= 100 )
		{
			if (pokemon1.getHp()<=0 || pokemon2.getHp()<=0)
			{
				// victory screen + attempt to catch pokemon +  go back to wilderness
				std::cout << "KONEC BOJE";
			}
			else
			{
				counter++;
				damageHolder = pok1Attack();
				std::setprecision(3);
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
					
					hit.setTextureRect(sf::IntRect(mRight, 17, 67, 69));
					hit.setPosition(bottomPok.getPosition());
					damage.setPosition(hit.getPosition());
					damage.move(sf::Vector2f(10, 10));
					int newc = 175 - (counter*damageHolder*1.75);
					healthBot.setTextureRect(sf::IntRect(13, 36, newc, 53));

					app.clear();

					
					app.draw(nameP1);
					app.draw(nameP2);
					app.draw(healthUp);
					app.draw(healthBot);
					app.draw(upperPok);
					app.draw(bottomPok);
					app.draw(hit);
					app.draw(damage);
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

					hit.setTextureRect(sf::IntRect(mRight, 17, 67, 69));
					hit.setPosition(upperPok.getPosition());
					damage.setPosition(hit.getPosition());
					damage.move(sf::Vector2f(10, 10));
					int newc = 175 - (counter*damageHolder*1.75);
					healthUp.setTextureRect(sf::IntRect(13, 36, newc, 53));
					app.clear();


					app.draw(nameP1);
					app.draw(nameP2);
					app.draw(healthUp);
					app.draw(healthBot);
					app.draw(upperPok);
					app.draw(bottomPok);
					app.draw(hit);
					app.draw(damage);

					app.display();
				}
			}
		}

		app.clear();

		app.draw(nameP1);
		app.draw(nameP2);
		app.draw(healthUp);
		app.draw(healthBot);
		app.draw(upperPok);
		app.draw(bottomPok);
		

		app.display();

	}

}
