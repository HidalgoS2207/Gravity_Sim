#include "Space.h"

Space::Space(std::pair<float, float> scr_size, unsigned int size)
	:
	size(size),
	cube(sf::Lines, 24),
	scr_size(scr_size),
	cube_scale(0.7)
{
	for (int i = 0; i < 24; i++)
	{
		cube[i].color = sf::Color::White;
	}

	rotation.x = 0.0;
	rotation.y = 0.0;
	rotation.z = 0.0;

	coor_center.first = scr_size.first / 2;
	coor_center.second = scr_size.second / 2;

	float space_screen_rel = (size / scr_size.first);
	scale_factor = (1 / space_screen_rel) * cube_scale;

	for (int i = 0; i < 8; i++)
	{
		space_vertex.emplace_back();
		natural_vertex_angle.emplace_back();
	}

	set_cube_vertex_coordinates();
}

Space::~Space()
{
}

void Space::rotate(double x, double y, double z)
{
	rotation.x += x;
	rotation.y += y;
	rotation.z += z;

	if (rotation.x >= 360.0)
	{
		rotation.x = rotation.x - 360.0;
	}

	if (rotation.y >= 360.0)
	{
		rotation.y = rotation.y - 360.0;
	}

	if (rotation.z >= 360.0)
	{
		rotation.z = rotation.z - 360.0;
	}
}

void Space::set_cube_vertex_coordinates()
{
	//------------vertex position for rotation natural angle------------------

	space_vertex[0].x = (-1) * (double(size) / 2);
	space_vertex[0].y = (-1) * (double(size) / 2);
	space_vertex[0].z = (-1) * (double(size) / 2);

	space_vertex[1].x = (1) * (double(size) / 2);
	space_vertex[1].y = (-1) * (double(size) / 2);
	space_vertex[1].z = (-1) * (double(size) / 2);

	space_vertex[2].x = (1) * (double(size) / 2);
	space_vertex[2].y = (1) * (double(size) / 2);
	space_vertex[2].z = (-1) * (double(size) / 2);

	space_vertex[3].x = (-1) * (double(size) / 2);
	space_vertex[3].y = (1) * (double(size) / 2);
	space_vertex[3].z = (-1) * (double(size) / 2);


	space_vertex[4].x = (-1) * (double(size) / 2);
	space_vertex[4].y = (-1) * (double(size) / 2);
	space_vertex[4].z = (1) * (double(size) / 2);

	space_vertex[5].x = (1) * (double(size) / 2);
	space_vertex[5].y = (-1) * (double(size) / 2);
	space_vertex[5].z = (1) * (double(size) / 2);

	space_vertex[6].x = (1) * (double(size) / 2);
	space_vertex[6].y = (1) * (double(size) / 2);
	space_vertex[6].z = (1) * (double(size) / 2);

	space_vertex[7].x = (-1) * (double(size) / 2);
	space_vertex[7].y = (1) * (double(size) / 2);
	space_vertex[7].z = (1) * (double(size) / 2);

	//-------------------------------------------------------------------

	//-------------natural angles for vertex-----------------------

	sphere_radius = sqrt((space_vertex[0].x * space_vertex[0].x) + (space_vertex[0].y * space_vertex[0].y) + (space_vertex[0].z * space_vertex[0].z));

	natural_vertex_angle[0].z = atan(space_vertex[0].y / space_vertex[0].x);
	natural_vertex_angle[0].x = atan(space_vertex[0].y / space_vertex[0].x);

	//-------------------------------------------------------------

	//screen representation of lines vertex---------------------------------------------------------------------------------

	cube[0] = sf::Vector2f(coor_center.first - ((size / 2) * scale_factor), coor_center.second - ((size / 2) * scale_factor));
	cube[7] = sf::Vector2f(coor_center.first - ((size / 2) * scale_factor), coor_center.second - ((size / 2) * scale_factor));
	cube[8] = sf::Vector2f(coor_center.first - ((size / 2) * scale_factor), coor_center.second - ((size / 2) * scale_factor));

	cube[1] = sf::Vector2f(coor_center.first + ((size / 2) * scale_factor), coor_center.second - ((size / 2) * scale_factor));
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

	//screen representation of lines vertex---------------------------------------------------------------------------------
}

void Space::update_cube_vertex()
{

}

void Space::draw(sf::RenderWindow& rw)
{
	rw.draw(cube);
}

void Space::update()
{
	update_cube_vertex();
}

float Space::get_rotation_x()
{
	return rotation.x;
}

float Space::get_rotation_y()
{
	return rotation.y;
}

float Space::get_rotation_z()
{
	return rotation.z;
}
