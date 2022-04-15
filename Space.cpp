#include "Space.h"

Space::Space(std::pair<float, float> scr_size, unsigned int size)
	:
	size(size),
	cube(sf::Lines, 24),
	scr_size(scr_size),
	cube_scale(0.7)
{
	for (int i = 0; i < 24;i++)
	{
		cube[i].color = sf::Color::White;
	}

	x_rot = 0.0;
	y_rot = 0.0;
	z_rot = 0.0;

	coor_center.first = scr_size.first / 2;
	coor_center.second = scr_size.second / 2;

	float space_screen_rel = (size / scr_size.first);
	scale_factor = (1 / space_screen_rel) * cube_scale;

	set_cube_vertex_coordinates();
}

Space::~Space()
{
}

void Space::rotate(double x, double y, double z)
{
	x_rot += x;
	y_rot += y;
	z_rot += z;

	if (x_rot >= 360.0)
	{
		x_rot = x_rot - 360.0;
	}

	if (y_rot >= 360.0)
	{
		y_rot = y_rot - 360.0;
	}

	if (z_rot >= 360.0)
	{
		z_rot = z_rot - 360.0;
	}
}

void Space::set_cube_vertex_coordinates()
{
	cube[0] = sf::Vector2f(coor_center.first - ((size/2) * scale_factor), coor_center.second - ((size/2) * scale_factor));
	cube[7] = sf::Vector2f(coor_center.first - ((size/2) * scale_factor), coor_center.second - ((size/2) * scale_factor));
	cube[8] = sf::Vector2f(coor_center.first - ((size/2) * scale_factor), coor_center.second - ((size/2) * scale_factor));

	cube[1] = sf::Vector2f(coor_center.first + ((size/2) * scale_factor), coor_center.second - ((size/2) * scale_factor));
	cube[2] = sf::Vector2f(coor_center.first + ((size / 2) * scale_factor), coor_center.second - ((size / 2) * scale_factor));
	cube[10] = sf::Vector2f(coor_center.first + ((size / 2) * scale_factor), coor_center.second - ((size / 2) * scale_factor));

	cube[3] = sf::Vector2f(coor_center.first + ((size / 2) * scale_factor), coor_center.second - ((size / 2) * scale_factor));
	cube[4] = sf::Vector2f(coor_center.first + ((size / 2) * scale_factor), coor_center.second - ((size / 2) * scale_factor));
	cube[12] = sf::Vector2f(coor_center.first + ((size / 2) * scale_factor), coor_center.second - ((size / 2) * scale_factor));

	cube[5] = sf::Vector2f(coor_center.first - ((size / 2) * scale_factor), coor_center.second - ((size / 2) * scale_factor));
	cube[6] = sf::Vector2f(coor_center.first - ((size / 2) * scale_factor), coor_center.second - ((size / 2) * scale_factor));
	cube[14] = sf::Vector2f(coor_center.first - ((size / 2) * scale_factor), coor_center.second - ((size / 2) * scale_factor));



	cube[9] = sf::Vector2f(coor_center.first - ((size / 2) * scale_factor), coor_center.second + ((size / 2) * scale_factor));
	cube[16] = sf::Vector2f(coor_center.first - ((size / 2) * scale_factor), coor_center.second + ((size / 2) * scale_factor));
	cube[23] = sf::Vector2f(coor_center.first - ((size / 2) * scale_factor), coor_center.second + ((size / 2) * scale_factor));

	cube[11] = sf::Vector2f(coor_center.first + ((size / 2) * scale_factor), coor_center.second + ((size / 2) * scale_factor));
	cube[17] = sf::Vector2f(coor_center.first + ((size / 2) * scale_factor), coor_center.second + ((size / 2) * scale_factor));
	cube[18] = sf::Vector2f(coor_center.first + ((size / 2) * scale_factor), coor_center.second + ((size / 2) * scale_factor));

	cube[13] = sf::Vector2f(coor_center.first + ((size / 2) * scale_factor), coor_center.second + ((size / 2) * scale_factor));
	cube[19] = sf::Vector2f(coor_center.first + ((size / 2) * scale_factor), coor_center.second + ((size / 2) * scale_factor));
	cube[20] = sf::Vector2f(coor_center.first + ((size / 2) * scale_factor), coor_center.second + ((size / 2) * scale_factor));

	cube[15] = sf::Vector2f(coor_center.first - ((size / 2) * scale_factor), coor_center.second + ((size / 2) * scale_factor));
	cube[21] = sf::Vector2f(coor_center.first - ((size / 2) * scale_factor), coor_center.second + ((size / 2) * scale_factor));
	cube[22] = sf::Vector2f(coor_center.first - ((size / 2) * scale_factor), coor_center.second + ((size / 2) * scale_factor));
}

void Space::draw(sf::RenderWindow& rw)
{
	rw.draw(cube);
}
