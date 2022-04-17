#pragma once

#include "Vertex3D.h"
#include "Particle_System.h"

#include <SFML/Graphics.hpp>

class Particle
{
public:
	Particle(double mass, double radius);
	~Particle();

	double get_mass();
	double get_radius();
	Vertex3D& get_speed();
	Vertex3D& get_position();
	sf::Vertex& get_proy_position();
	void calc_interactions(Particle_System& ps);

	void set_mass(double m);
	void set_radius(double r);
	void set_speed(double x, double y, double z);
	void set_position(double x, double y, double z, double vx, double vy);
private:
	double mass;
	double radius;
	Vertex3D speed;
	Vertex3D position;

	sf::Vertex v_rep;
};