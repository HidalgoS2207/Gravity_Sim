#include "Sim_Core.h"

Sim_Core::Sim_Core(sf::RenderWindow& rw)
	:
	rw(rw),
	tic(0.001),
	gravitational_constant(6.67430 * (pow(10, -11))),
	space({ rw.getSize().x,rw.getSize().y }, 3000)
{
	std::cout << gravitational_constant << '\n';
}

Sim_Core::~Sim_Core()
{
}

void Sim_Core::update()
{
}

void Sim_Core::draw()
{
	space.draw(rw);
}
