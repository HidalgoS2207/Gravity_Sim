#pragma once

#include <SFML/Graphics.hpp>

#include "Space.h"
#include "Particle_System.h"

#include <vector>
#include <math.h>
#include <numeric>
#include <iostream>
#include <utility>
#include <string>
#include <random>

class Sim_Core
{
public:
	Sim_Core(sf::RenderWindow& rw);
	~Sim_Core();

	void update();
	void draw();
private:
	sf::RenderWindow& rw;

	float tic;

	float rot_stps;

	sf::Font font1;
	sf::Font font2;

	std::vector<sf::Text> signs;

	Space space;
	Particle_System particle_system;

	const double gravitational_constant;

	//-------METHODS-------------------

	void set_sign(sf::Font& font , sf::Text & to,std::string text,int size, int x_pos,int y_pos);
	void kbd_input();	

	//---------------------------------

};