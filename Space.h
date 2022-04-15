#pragma once

#include <math.h>

#include <SFML/Graphics.hpp>

class Space
{
public:
	Space(std::pair<float, float> scr_size,unsigned int size);
	~Space();

	void rotate(double x, double y, double z);

	void draw(sf::RenderWindow& rw);
private:
	unsigned int size;

	double x_rot;
	double y_rot;
	double z_rot;

	std::pair<float, float> scr_size;
	std::pair<float, float> coor_center; //pxls

	const float cube_scale; //space occupied in screen by space cube representation
	float scale_factor; //factor to properly scale cube size to match cube scale

	sf::VertexArray cube; //2d coordinates for cube graphic projection

	void set_cube_vertex_coordinates();
};