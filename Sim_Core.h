#pragma once

#include <SFML/Graphics.hpp>

#include "Particle.h"
#include "Space.h"

#include <vector>
#include <math.h>
#include <numeric>
#include <iostream>
#include <utility>

class Sim_Core
{
public:
	Sim_Core(sf::RenderWindow& rw);
	~Sim_Core();

	void update();
	void draw();
private:
	sf::RenderWindow& rw;

	std::vector<Particle*> particles_system;
	Space space;

	float tic;

	const double gravitational_constant;

};