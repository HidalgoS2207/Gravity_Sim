#include "Space.h"

Space::Space(std::pair<double, double> scr_size, unsigned int size)
	:
	size(size),
	cube(sf::Lines, 24),
	scr_size(scr_size),
	cube_scale(0.5),
	rx(RotMatrix::RotAxis::rx),
	ry(RotMatrix::RotAxis::ry),
	rz(RotMatrix::RotAxis::rz)
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

	set_space_plane(((1.0) * size / 2.0), 0, 0, -1.0, 0, 0);
	set_space_plane(((-1.0) * size / 2.0), 0, 0, 1.0, 0, 0);
	set_space_plane(0, ((1.0) * size / 2.0), 0, 0, -1.0, 0);
	set_space_plane(0, ((-1.0) * size / 2.0), 0, 0, 1.0, 0);
	set_space_plane(0, 0, ((1.0) * size / 2.0), 0, 0, -1.0);
	set_space_plane(0, 0, ((-1.0) * size / 2.0), 0, 0, 1.0); 

	for (auto& pl : planes)
	{
		std::cout <<"\nNormal : " << pl->get_normal().x << " - " << pl->get_normal().y << " - " << pl->get_normal().z << '\n';
		std::cout << "Point : " << pl->get_point().x << " - " << pl->get_point().y << " - " << pl->get_point().z << '\n';
	}

	std::cout << "\n\n\n";
}

Space::~Space()
{
	for (int i = 0; i < planes.size(); i++)
	{
		delete planes[i];
	}
}

void Space::x_rotate(double x)
{
	rotation.x += x;

	if (rotation.x >= 360.0)
	{
		rotation.x = rotation.x - 360.0;
	}

	rx.rotate(space_vertex[0], x);
	rx.rotate(space_vertex[1], x);
	rx.rotate(space_vertex[2], x);
	rx.rotate(space_vertex[3], x);

	rx.rotate(space_vertex[4], x);
	rx.rotate(space_vertex[5], x);
	rx.rotate(space_vertex[6], x);
	rx.rotate(space_vertex[7], x);

	update_cube_vertex(0, 7, 8, 0);
	update_cube_vertex(1, 2, 10, 1);
	update_cube_vertex(3, 4, 12, 2);
	update_cube_vertex(5, 6, 14, 3);

	update_cube_vertex(9, 16, 23, 4);
	update_cube_vertex(11, 17, 18, 5);
	update_cube_vertex(13, 19, 20, 6);
	update_cube_vertex(15, 21, 22, 7);
}

void Space::y_rotate(double y)
{
	rotation.y += y;

	if (rotation.y >= 360.0)
	{
		rotation.y = rotation.y - 360.0;
	}

	ry.rotate(space_vertex[0], y);
	ry.rotate(space_vertex[1], y);
	ry.rotate(space_vertex[2], y);
	ry.rotate(space_vertex[3], y);

	ry.rotate(space_vertex[4], y);
	ry.rotate(space_vertex[5], y);
	ry.rotate(space_vertex[6], y);
	ry.rotate(space_vertex[7], y);

	update_cube_vertex(0, 7, 8, 0);
	update_cube_vertex(1, 2, 10, 1);
	update_cube_vertex(3, 4, 12, 2);
	update_cube_vertex(5, 6, 14, 3);

	update_cube_vertex(9, 16, 23, 4);
	update_cube_vertex(11, 17, 18, 5);
	update_cube_vertex(13, 19, 20, 6);
	update_cube_vertex(15, 21, 22, 7);
}

void Space::z_rotate(double z)
{
	rotation.z += z;

	if (rotation.z >= 360.0)
	{
		rotation.z = rotation.z - 360.0;
	}

	rz.rotate(space_vertex[0], z);
	rz.rotate(space_vertex[1], z);
	rz.rotate(space_vertex[2], z);
	rz.rotate(space_vertex[3], z);

	rz.rotate(space_vertex[4], z);
	rz.rotate(space_vertex[5], z);
	rz.rotate(space_vertex[6], z);
	rz.rotate(space_vertex[7], z);

	update_cube_vertex(0, 7, 8, 0);
	update_cube_vertex(1, 2, 10, 1);
	update_cube_vertex(3, 4, 12, 2);
	update_cube_vertex(5, 6, 14, 3);

	update_cube_vertex(9, 16, 23, 4);
	update_cube_vertex(11, 17, 18, 5);
	update_cube_vertex(13, 19, 20, 6);
	update_cube_vertex(15, 21, 22, 7);
}

void Space::set_cube_vertex_coordinates()
{
	sphere_radius = sqrt(((double(size) / 2) * (double(size) / 2)) + ((double(size) / 2) * (double(size) / 2)) + ((double(size) / 2) * (double(size) / 2)));

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

	//screen representation of lines vertex---------------------------------------------------------------------------------

	//rotation.x = 35.2643940570924;
	//rotation.z = 45;

	update_cube_vertex(0, 7, 8, 0);
	update_cube_vertex(1, 2, 10, 1);
	update_cube_vertex(3, 4, 12, 2);
	update_cube_vertex(5, 6, 14, 3);

	update_cube_vertex(9, 16, 23, 4);
	update_cube_vertex(11, 17, 18, 5);
	update_cube_vertex(13, 19, 20, 6);
	update_cube_vertex(15, 21, 22, 7);

	//screen representation of lines vertex---------------------------------------------------------------------------------
}

void Space::update_cube_vertex(int va, int vb, int vc, int idx)
{
	/*cube[va] = sf::Vector2f(coor_center.first + ((space_vertex[idx].x * sin((rotation.x * PI) / 180)) * scale_factor), coor_center.second + ((space_vertex[idx].z * sin((rotation.z * PI) / 180)) * scale_factor));
	cube[vb] = sf::Vector2f(coor_center.first + ((space_vertex[idx].x * sin((rotation.x * PI) / 180)) * scale_factor), coor_center.second + ((space_vertex[idx].z * sin((rotation.z * PI) / 180)) * scale_factor));
	cube[vc] = sf::Vector2f(coor_center.first + ((space_vertex[idx].x * sin((rotation.x * PI) / 180)) * scale_factor), coor_center.second + ((space_vertex[idx].z * sin((rotation.z * PI) / 180)) * scale_factor));*/

	cube[va] = sf::Vector2f(coor_center.first + (space_vertex[idx].x * scale_factor), coor_center.first + (space_vertex[idx].z * scale_factor));
	cube[vb] = sf::Vector2f(coor_center.first + (space_vertex[idx].x * scale_factor), coor_center.first + (space_vertex[idx].z * scale_factor));
	cube[vc] = sf::Vector2f(coor_center.first + (space_vertex[idx].x * scale_factor), coor_center.first + (space_vertex[idx].z * scale_factor));
}

void Space::inverse_kinematic_heu(Vertex3D& v3d, double x1, double y1, double z1, double x0, double y0, double z0)
{}

void Space::set_space_plane(double px, double py, double pz, double nx, double ny, double nz)
{
	Vertex3D point;
	Vertex3D normal;

	point.reset();
	normal.reset();
	point.set_values(px, py, pz);
	normal.set_values(nx, ny, nz);

	Plane* p = new Plane(normal, point);

	planes.push_back(p);
}

void Space::draw(sf::RenderWindow& rw)
{
	rw.draw(cube);
}

void Space::update()
{
}

double Space::get_rotation_x()
{
	return rotation.x;
}

double Space::get_rotation_y()
{
	return rotation.y;
}

double Space::get_rotation_z()
{
	return rotation.z;
}

double Space::get_scale_factor()
{
	return scale_factor;
}

double Space::get_size()
{
	return size;
}
