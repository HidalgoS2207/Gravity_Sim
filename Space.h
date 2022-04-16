#pragma once

#include <math.h>
#include <vector>

#include "Vertex3D.h"
#include "RotMat.h"

#include <SFML/Graphics.hpp>

class Space
{
public:
	Space(std::pair<float, float> scr_size, unsigned int size);
	~Space();

	void x_rotate(double x);
	void y_rotate(double y);
	void z_rotate(double z);

	void draw(sf::RenderWindow& rw);
	void update();

	float get_rotation_x();
	float get_rotation_y();
	float get_rotation_z();
private:
	unsigned int size;

	Vertex3D rotation;
	std::vector<Vertex3D> space_vertex;
	std::vector<Vertex3D> natural_vertex_angle;
	double sphere_radius;
	RotMatrix rx;
	RotMatrix ry;
	RotMatrix rz;

	std::pair<float, float> scr_size;
	std::pair<float, float> coor_center; //pxls

	const float cube_scale; //space occupied in screen by space cube representation
	float scale_factor; //factor to properly scale cube size to match cube scale

	sf::VertexArray cube; //2d coordinates for cube graphic projection

	void set_cube_vertex_coordinates();
	void update_cube_vertex(int va,int vb,int vc,int idx);
	void inverse_kinematic_heu(Vertex3D& v3d,double x1, double y1, double z1,double x0,double y0,double z0);
};