// Kaikkia kivoja helpper funktiota joilla k‰tket‰‰n j‰nni‰ juttuja

#define WIN32_MEAN_AND_LEAN

#include <Windows.h>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <cstdlib>

#include "Vector.h"

#define _TO_STRING(value) #value
#define TO_STRING(value) _TO_STRING(value)

using namespace sf;

struct Ball
{
	Vec2 position;
	Vec2 velocity;
};

typedef std::vector<Ball> PalloLista;

#define LOADTEXTURE(p_var, p_file) \
	sf::Image p_var##img;\
	if(!p_var##img.loadFromFile(p_file)) { printf("\nVIRHEELLINEN TIEDOSTON NIMI! (%s) \n", TO_STRING(p_var)); return -1; }\
	p_var##img.createMaskFromColor(sf::Color());\
	sf::Texture p_var##tex;\
	p_var##tex.loadFromImage(p_var##img);\
	sf::Sprite p_var;\
	p_var.setTexture(p_var##tex);


void updateBackend(Window &window)
{
	sf::Event event;

	while (window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			window.close();
	}
}

int randomRange(int min, int max){
	return min + (rand() % (int)(max - min + 1));
}