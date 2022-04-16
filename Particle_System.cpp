#include "Particle_System.h"

Particle_System::Particle_System()
{
}

Particle_System::~Particle_System()
{
	for (int i = 0; i < particles.size(); i++)
	{
		delete particles[i];
	}

	particles.clear();
}

void Particle_System::update()
{
}

void Particle_System::draw(sf::RenderWindow& rw)
{
	for (auto& x : particles)
	{
		rw.draw(&(x->get_proy_position()),1,sf::PrimitiveType::Points);
	}
}

void Particle_System::generate_random_particles(double size)
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<> dis(size * 0.15, size * 0.85);

	Particle* p = new Particle(1, 1);
	p->set_position(dis(gen), dis(gen), dis(gen));

	particles.push_back(p);
}
