#pragma once

#include "Particle.h"
#include "RotMat.h"
#include "Vertex3D.h"

#include <SFML/Graphics.hpp>

#include <random>

class Particle_System
{
public:
	Particle_System(double space_size,double scale_factor,sf::RenderWindow& rw);
	~Particle_System();

	void update();
	void draw();

	void x_rotate(double x);
	void y_rotate(double y);
	void z_rotate(double z);

	void generate_random_particles(int num_particles);
private:
	std::vector<Particle*> particles;

	sf::RenderWindow& rw;
	std::pair<double, double> screen_size;
	std::pair<double, double> coor_center; //pxls

	double space_size;
	double scale_factor;

	RotMatrix rx;
	RotMatrix ry;
	RotMatrix rz;

	Vertex3D rotation;	
};