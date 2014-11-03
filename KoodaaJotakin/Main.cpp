#include "Main.h"
#include "ParticleSystem.h"

/*
_  __               _                    _       _        _    _
| |/ /              | |                  | |     | |      | |  (_)
| ' / ___   ___   __| | __ _  __ _       | | ___ | |_ __ _| | ___ _ __
|  < / _ \ / _ \ / _` |/ _` |/ _` |  _   | |/ _ \| __/ _` | |/ / | '_ \
| . \ (_) | (_) | (_| | (_| | (_| | | |__| | (_) | || (_| |   <| | | | |
|_|\_\___/ \___/ \__,_|\__,_|\__,_|  \____/ \___/ \__\__,_|_|\_\_|_| |_|

*/

/*

Ohjeet:

-> Paina F5 ajaaksesi peli
-> Muokkaa ohjelmaa, ja aja ohjelma uudelleen nähdäksesi muutokset!
-> Ohjelmaan on koodattu tarkoituksella bugeja, pystytkö korjaamaan ne?


HUOM:  Muokkaa koodia aivan vapaasti, sen hajottaminen ei haittaa koska siitä on backup :)

       (Numeroita vaihtelemalla saa kaikkea jännää tapahtumaan.)

*/

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	// Ohjelman alustusta
	RenderWindow window(sf::VideoMode(800, 600), "Koodaa jotakin");

	// Maksimi framemäärä, hidastaa pelin ajamista sopivaksi
	window.setFramerateLimit(60);

	// Ladataan mediat
	LOADTEXTURE(playerImage, "pallo1.png");
	LOADTEXTURE(ballImage, "pallo2.png");
	LOADTEXTURE(particleImage, "particle.png");

	// Alustetaan pelaajan tiedot
	Vec2 playerPosition(400, 300);    // Pelaajan aloitus koordinaatit keskelle ruutua
	float playerSpeed = 3.f;          // Pelaajan liikkumis nopeus

	// Lista kerättävistä palloista
	PalloLista palloLista;
	float ballSpeed = 5.f;            // Pallon nopeus

	// Partikkeli järjestelmän luonti
	ParticleSystem particleSystem(&window);

	for (unsigned i = 0; i < 10; ++i) // Lisätään kymmenen palloa kentälle (koita vaihtaa määrää!)
	{
		Ball pallo;

		// Sijoitetaan pallo satunnaiselle sijainnille x/y koordinaateilla
		pallo.position.x = randomRange(0, 200);
		pallo.position.y = randomRange(0, 200);

		// annetaan pallolle satunnainen nopeus pallon nopeuden pohjalta
		pallo.velocity.x = randomRange(-ballSpeed, ballSpeed);
		pallo.velocity.y = randomRange(-ballSpeed, ballSpeed); //säädä nopeutta ylempää, ballSpeed muuttujan luonnin kohdalta!

		// Lisätään juuri luotu pallo listaan
		palloLista.push_back(pallo);
	}

	// Pää looppi
	while (window.isOpen())
	{
		// ########## LOGIIKKA ##########
		updateBackend(window); // päivitetään kaikkea jännää taustalla

		// Pelaajan liikkuminen 

		// -> liikkumisessa on bugi! koita korjata se
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			playerPosition.y -= playerSpeed * 1.2f;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			playerPosition.y += playerSpeed * 1.2f;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			playerPosition.x -= playerSpeed;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			playerPosition.x += playerSpeed;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		{
			// Lisätään partikkeleita!
			                            //määrä, sijainti, nopeus, minimi elinaika, maksimi elinaika 
			particleSystem.addParticles(5, playerPosition, 5, 15, 25);
		}

		// Vihreiden pallojen liike

		for (unsigned i = 0; i < palloLista.size(); ++i)
		{
			palloLista[i].position += palloLista[i].velocity;

			// kimpoaminen seinästä
			if (palloLista[i].position.x < 0)
				palloLista[i].velocity.x = ballSpeed;

			if (palloLista[i].position.x > 800)
				palloLista[i].velocity.x = -ballSpeed;

			if (palloLista[i].position.y < 0)
				palloLista[i].velocity.y = ballSpeed;

			if (palloLista[i].position.y > 600)
				palloLista[i].velocity.y = -ballSpeed;


			// Pelaajan törmääminen palloon

			// Lasketaan pituus.
			float distance = (palloLista[i].position - playerPosition).getLenght();

			// jos välimatka pienempi kuin luku, törmäys on tapahtunut
			if (distance < 32)
			{
				// Lisätään räjähdys, koska räjähdykset ovat kivoja !
				//määrä, sijainti, nopeus, minimi elinaika, maksimi elinaika 
				particleSystem.addParticles(55, palloLista[i].position, 5, 15, 25);

				// Poistetaan pallo
				palloLista.erase(palloLista.begin() + i);
			}
		}

		// ########## PIIRTO ##########
		window.clear(sf::Color(150, 20, 20, 255)); // Tyhjennetään tausta värillä (R, G, B, Alpha);
		
		playerImage.setPosition(playerPosition.x, playerPosition.y); // Asetetaan kuva pelaajan sijaintiin
		window.draw(playerImage); //piirretään pelaajan kuva ruudulle

		for (unsigned i = 0; i < palloLista.size(); ++i) //Käydään lista läpi palloista
		{
			Ball pallo = palloLista[i]; // otetaan listasta pallo

			// -16 keskittää kuvan
			ballImage.setPosition(pallo.position.x - 16, pallo.position.y - 16); // Sijoitetaan pallo kuva listassa olevan pallon kohdalle
			window.draw(ballImage); // ja piirretään se
		}

		// Piirretään partikkelit
		particleSystem.draw(particleImage);

		window.display(); // piirretään frame ruudulle
	}

	return 0;
}