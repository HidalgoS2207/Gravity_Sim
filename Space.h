#pragma once

#include <math.h>
#include <vector>
#include <iostream>

#include "Vertex3D.h"
#include "RotMat.h"
#include "Plane.h"

#include <SFML/Graphics.hpp>

class Space
{
public:
	Space(std::pair<double, double> scr_size, unsigned int size);
	~Space();

	void x_rotate(double x);
	void y_rotate(double y);
	void z_rotate(double z);

	void draw(sf::RenderWindow& rw);
	void update();

	double get_rotation_x();
	double get_rotation_y();
	double get_rotation_z();

	double get_scale_factor();
	double get_size();
private:
	unsigned int size;

	Vertex3D rotation;
	std::vector<Vertex3D> space_vertex;
	std::vector<Vertex3D> natural_vertex_angle;
	double sphere_radius;
	RotMatrix rx;
	RotMatrix ry;
	RotMatrix rz;

	std::pair<double, double> scr_size;
	std::pair<double, double> coor_center; //pxls

	std::vector<Plane> planes;

	const double cube_scale; //space occupied in screen by space cube representation
	double scale_factor; //factor to properly scale cube size to match cube scale

	sf::VertexArray cube; //2d coordinates for cube graphic projection

	void set_cube_vertex_coordinates();
	void update_cube_vertex(int va,int vb,int vc,int idx);
	void inverse_kinematic_heu(Vertex3D& v3d,double x1, double y1, double z1,double x0,double y0,double z0);
	void set_space_plane(double px, double py,double pz,double nx,double ny,double nz);
};