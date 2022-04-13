#pragma once

#include <SFML/Graphics.hpp>

class Sim_Core
{
public:
	Sim_Core(sf::RenderWindow& rw);
	~Sim_Core();
private:
	sf::RenderWindow& rw;
};