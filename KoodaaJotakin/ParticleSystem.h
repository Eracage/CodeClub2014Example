#include <vector>
#include "Vector.h"

struct Particle
{
	bool alive;
	unsigned ttl;
	Vec2 pos;
	Vec2 speed;
};

class ParticleSystem
{
private:
	std::vector<Particle> particles;

	sf::RenderWindow *window;

public:
	ParticleSystem(sf::RenderWindow *window)
		: window(window)
	{ }

	void addParticles(unsigned count, Vec2 position, int speed, int ttlMin, int ttlMax)
	{
		for (unsigned i = 0; i < count; ++i)
		{
			Particle part;
			part.alive = true;
			part.pos = position;
			part.ttl = randomRange(ttlMin, ttlMax);
			part.speed.x = randomRange(-speed, speed);
			part.speed.y = randomRange(-speed, speed);

			particles.push_back(part);
		}

	}

	void draw(sf::Sprite sprite)
	{
		for (unsigned i = 0; i < particles.size(); ++i)
		{
			if (!particles[i].alive)
				continue;

			particles[i].pos += particles[i].speed;

			--particles[i].ttl;

			if (particles[i].ttl <= 0)
				particles[i].alive = false;

			sprite.setPosition(particles[i].pos.x, particles[i].pos.y);
			window->draw(sprite);
		}
	}

};