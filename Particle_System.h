#pragma once

#include "Particle.h"

#include <SFML/Graphics.hpp>

#include <random>

class Particle_System
{
public:
	Particle_System();
	~Particle_System();

	void update();
	void draw(sf::RenderWindow& r);

	void generate_random_particles(double size);
private:
	std::vector<Particle*> particles;
};