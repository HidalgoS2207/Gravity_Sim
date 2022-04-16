#include "Particle.h"

Particle::Particle(double mass, double radius)
	:
	mass(mass),
	radius(radius)
{
	vx.color = sf::Color::Red;
}

Particle::~Particle()
{}

double Particle::get_mass()
{
	return mass;
}

double Particle::get_radius()
{
	return radius;
}

Vertex3D& Particle::get_speed()
{
	return speed;
}

Vertex3D& Particle::get_position()
{
	return position;
}

sf::Vertex& Particle::get_proy_position()
{
	return v_rep;
}

void Particle::set_mass(double m)
{
	mass = m;
}

void Particle::set_radius(double r)
{
	radius = r;
}

void Particle::set_speed(double x, double y, double z)
{
	speed.x = x;
	speed.y = y;
	speed.z = z;
}

void Particle::set_position(double x, double y, double z, double vx,double vy)
{
	position.x = x;
	position.y = y;
	position.z = z;

	v_rep.position.x = vx;
	v_rep.position.y = vy;
}
