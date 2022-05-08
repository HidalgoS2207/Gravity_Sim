#pragma once

#include "Vertex3D.h"

#include <SFML/Graphics.hpp>

class Particle
{
public:
	Particle(double mass, double radius, unsigned int ID,bool fixed);
	~Particle();

	double get_mass();
	double get_radius();
	Vertex3D& get_speed();
	Vertex3D& get_position();
	sf::Vertex& get_proy_position();
	unsigned int get_id();
	bool get_state();
	void update(double tic, double limit);

	void set_mass(double m);
	void set_radius(double r);
	void set_speed(double x, double y, double z);
	void set_position(double x, double y, double z, double vx, double vy);
	void set_force(Vertex3D& force);

	void toggle_state();
private:
	double mass;
	double radius;
	unsigned int ID;
	Vertex3D speed;
	Vertex3D position;
	Vertex3D force;

	bool state;

	Vertex3D last_pos;

	sf::Vertex v_rep;

	int check_bounce(double pos, double limit);
	void correct_pos(double limit);

	bool fixed;
};