#include "Particle.h"

Particle::Particle(double mass, double radius)
	:
	mass(mass),
	radius(radius)
{
	v_rep.color = sf::Color::Red;

	speed.reset();
	force.reset();
	position.reset();

	last_pos.reset();
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

void Particle::update(double tic, double limit)
{
	speed.x = (speed.x + ((force.x / mass) * tic)) * (check_bounce(abs(position.x), limit / 2.0));
	speed.y = (speed.y + ((force.y / mass) * tic)) * (check_bounce(abs(position.y), limit / 2.0));
	speed.z = (speed.z + ((force.z / mass) * tic)) * (check_bounce(abs(position.z), limit / 2.0));

	correct_pos(limit / 2.0);

	last_pos.x = position.x;
	last_pos.y = position.y;
	last_pos.z = position.z;

	position.x = position.x + (speed.x * tic);
	position.y = position.y + (speed.y * tic);
	position.z = position.z + (speed.z * tic);
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

	update(0.01, std::numeric_limits<double>::max());
}

void Particle::set_position(double x, double y, double z, double vx, double vy)
{
	position.x = x;
	position.y = y;
	position.z = z;

	v_rep.position.x = vx;
	v_rep.position.y = vy;
}

int Particle::check_bounce(double pos, double limit)
{
	return pos > limit ? (-1) : 1;
}

void Particle::correct_pos(double limit)
{
	position.x = abs(position.x) > (limit) ? (limit * (position.x / (abs(position.x)))) : position.x;
	position.y = abs(position.y) > (limit) ? (limit * (position.y / (abs(position.y)))) : position.y;
	position.z = abs(position.z) > (limit) ? (limit * (position.z / (abs(position.z)))) : position.z;
}
