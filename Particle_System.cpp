#include "Particle_System.h"

Particle_System::Particle_System(double space_size, double scale_factor, sf::RenderWindow& rw)
	:
	rw(rw),
	space_size(space_size),
	scale_factor(scale_factor),
	rx(RotMatrix::RotAxis::rx),
	ry(RotMatrix::RotAxis::ry),
	rz(RotMatrix::RotAxis::rz),
	gravitational_constant(6.67430 * (pow(10, -11)))
{
	screen_size.first = rw.getSize().x;
	screen_size.second = rw.getSize().y;

	coor_center.first = screen_size.first / 2.0;
	coor_center.second = screen_size.second / 2.0;

	rotation.x = 0.0;
	rotation.y = 0.0;
	rotation.z = 0.0;
}

Particle_System::~Particle_System()
{
	for (int i = 0; i < particles.size(); i++)
	{
		delete particles[i];
	}

	particles.clear();
}

void Particle_System::update(double tic)
{
	for (auto& p : particles)
	{
		p->calc_interactions(*this);
	}
}

void Particle_System::draw()
{
	for (auto& p : particles)
	{
		rw.draw(&(p->get_proy_position()), 1, sf::PrimitiveType::Points);
	}
}

void Particle_System::x_rotate(double x)
{
	rotation.x += x;

	if (rotation.x >= 360.0)
	{
		rotation.x = rotation.x - 360.0;
	}

	for (auto& p : particles)
	{
		rx.rotate(p->get_position(), x);
		p->get_proy_position().position.x = (coor_center.first + (p->get_position().x * scale_factor));
		p->get_proy_position().position.y = (coor_center.second + (p->get_position().z * scale_factor));
	}
}

void Particle_System::y_rotate(double y)
{
	rotation.y += y;

	if (rotation.y >= 360.0)
	{
		rotation.y = rotation.y - 360.0;
	}

	for (auto& p : particles)
	{
		ry.rotate(p->get_position(), y);
		p->get_proy_position().position.x = (coor_center.first + (p->get_position().x * scale_factor));
		p->get_proy_position().position.y = (coor_center.second + (p->get_position().z * scale_factor));
	}
}

void Particle_System::z_rotate(double z)
{
	rotation.z += z;

	if (rotation.z >= 360.0)
	{
		rotation.z = rotation.z - 360.0;
	}

	for (auto& p : particles)
	{
		rz.rotate(p->get_position(), z);
		p->get_proy_position().position.x = (coor_center.first + (p->get_position().x * scale_factor));
		p->get_proy_position().position.y = (coor_center.second + (p->get_position().z * scale_factor));
	}
}

void Particle_System::generate_random_particles(int num_particles)
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<> dis(((-1) * (space_size / 2)) * 0.85, ((1) * (space_size / 2)) * 0.85);

	for (int i = 0; i < num_particles; i++)
	{
		Particle* p = new Particle(1, 1);

		double x_pos = dis(gen);
		double y_pos = dis(gen);
		double z_pos = dis(gen);

		double vx_rep = (coor_center.first + (x_pos * scale_factor));
		double vy_rep = (coor_center.second + (y_pos * scale_factor));

		p->set_position(x_pos, y_pos, z_pos, vx_rep, vy_rep);

		particles.push_back(p);
	}
}
