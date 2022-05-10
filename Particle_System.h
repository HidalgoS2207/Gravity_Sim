#pragma once

#include "Particle.h"
#include "RotMat.h"
#include "Vertex3D.h"
#include "Plane.h"

#include <SFML/Graphics.hpp>

#include <random>
#include <math.h>
#include <iostream>

class Particle_System
{
private:
	enum CameraRotAngle
	{
		crx,
		cry,
		crz
	};
public:
	Particle_System(double space_size,double scale_factor,sf::RenderWindow& rw);
	~Particle_System();

	void update(double tic);
	void draw();
	int get_num_particles();

	void x_rotate(double x);
	void y_rotate(double y);
	void z_rotate(double z);

	void camera_x_rotate(double x);
	void camera_y_rotate(double y);
	void camera_z_rotate(double z);

	void generate_random_particles(int num_particles);
	void generate_random_particles_nd(int num_particles);
	void generate_particle(double mass, double radius, Vertex3D pos, Vertex3D speed,bool fixed);
private:
	void update_attraction_forces(Particle* q,Particle * p);
	void check_scapes(Particle * p);
	void clean_system();
	int check_quadrant(double x,double y,double h);

	const double PI;

	std::vector<Particle*> particles;

	Vertex3D focal_point;

	const double gravitational_constant;

	sf::RenderWindow& rw;
	std::pair<double, double> screen_size;
	std::pair<double, double> coor_center; //pxls

	std::vector<int> set_to_destroy;

	double space_size;
	double scale_factor;

	RotMatrix rx;
	RotMatrix ry;
	RotMatrix rz;

	Vertex3D camera_angle;
	Vertex3D rotation;

	void update_projection(Particle * p);
};