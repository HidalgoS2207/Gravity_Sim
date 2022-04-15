#pragma once

#include <math.h>
#include <vector>

#include <SFML/Graphics.hpp>

class Space
{
public:
	Space(std::pair<float, float> scr_size,unsigned int size);
	~Space();

	void rotate(double x, double y, double z);

	void draw(sf::RenderWindow& rw);
	void update();

	float get_rotation_x();
	float get_rotation_y();
	float get_rotation_z();
private:
	unsigned int size;

	sf::Vector3f rotation;
	std::vector<sf::Vector3f> space_vertex;
	std::vector<sf::Vector3f> natural_vertex_angle;
	double sphere_radius;

	std::pair<float, float> scr_size;
	std::pair<float, float> coor_center; //pxls

	const float cube_scale; //space occupied in screen by space cube representation
	float scale_factor; //factor to properly scale cube size to match cube scale

	sf::VertexArray cube; //2d coordinates for cube graphic projection

	void set_cube_vertex_coordinates();
	void update_cube_vertex();
};