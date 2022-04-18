#include "Particle_System.h"

Particle_System::Particle_System(double space_size, double scale_factor, sf::RenderWindow& rw)
	:
	rw(rw),
	space_size(space_size),
	scale_factor(scale_factor),
	rx(RotMatrix::RotAxis::rx),
	ry(RotMatrix::RotAxis::ry),
	rz(RotMatrix::RotAxis::rz),
	gravitational_constant(6.67430 * (pow(10, -11)))
{
	screen_size.first = rw.getSize().x;
	screen_size.second = rw.getSize().y;

	coor_center.first = screen_size.first / 2.0;
	coor_center.second = screen_size.second / 2.0;

	rotation.reset();
	camera_angle.reset();

	camera_angle.x = 90;
}

Particle_System::~Particle_System()
{
	for (int i = 0; i < particles.size(); i++)
	{
		delete particles[i];
	}

	particles.clear();
}

void Particle_System::update(double tic)
{
	for (auto& p : particles)
	{
		p->update(tic, space_size);

		//p->get_proy_position().position.x = (coor_center.first + (p->get_position().x * scale_factor));
		//p->get_proy_position().position.y = (coor_center.second + (p->get_position().z * scale_factor));
		update_projection(p);
	}
}

void Particle_System::draw()
{
	for (auto& p : particles)
	{
		rw.draw(&(p->get_proy_position()), 1, sf::PrimitiveType::Points);
	}
}

int Particle_System::get_num_particles()
{
	return particles.size();
}

void Particle_System::x_rotate(double x)
{
	rotation.x += x;

	if (rotation.x >= 360.0)
	{
		rotation.x = rotation.x - 360.0;
	}

	for (auto& p : particles)
	{
		rx.rotate(p->get_position(), x);
		rx.rotate(p->get_speed(), x);
		//update_projection(p,CameraRotAngle::crx);
		p->get_proy_position().position.x = (coor_center.first + (p->get_position().x * scale_factor));
		p->get_proy_position().position.y = (coor_center.second + (p->get_position().z * scale_factor));
	}
}

void Particle_System::y_rotate(double y)
{
	rotation.y += y;

	if (rotation.y >= 360.0)
	{
		rotation.y = rotation.y - 360.0;
	}

	for (auto& p : particles)
	{
		ry.rotate(p->get_position(), y);
		ry.rotate(p->get_speed(), y);
		//update_projection(p,CameraRotAngle::cry);
		p->get_proy_position().position.x = (coor_center.first + (p->get_position().x * scale_factor));
		p->get_proy_position().position.y = (coor_center.second + (p->get_position().z * scale_factor));
	}
}

void Particle_System::z_rotate(double z)
{
	rotation.z += z;

	if (rotation.z >= 360.0)
	{
		rotation.z = rotation.z - 360.0;
	}

	for (auto& p : particles)
	{
		rz.rotate(p->get_position(), z);
		rz.rotate(p->get_speed(), z);
		//update_projection(p,CameraRotAngle::crz);
		p->get_proy_position().position.x = (coor_center.first + (p->get_position().x * scale_factor));
		p->get_proy_position().position.y = (coor_center.second + (p->get_position().z * scale_factor));
	}
}

void Particle_System::camera_x_rotate(double x)
{
	camera_angle.x += x;

	if (camera_angle.x >= 360.0)
	{
		camera_angle.x = camera_angle.x - 360.0;
	}

	for (auto& p : particles)
	{
		update_projection(p);
	}
}

void Particle_System::camera_y_rotate(double y)
{
	camera_angle.y += y;

	if (camera_angle.y >= 360.0)
	{
		camera_angle.y = camera_angle.y - 360.0;
	}

	for (auto& p : particles)
	{
		update_projection(p);
	}
}

void Particle_System::camera_z_rotate(double z)
{
	camera_angle.z += z;

	if (camera_angle.z >= 360.0)
	{
		camera_angle.z = camera_angle.z - 360.0;
	}

	for (auto& p : particles)
	{
		update_projection(p);
	}
}

void Particle_System::generate_random_particles(int num_particles)
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<> dis(((-1) * (space_size / 2)) * 0.85, ((1) * (space_size / 2)) * 0.85);
	std::uniform_real_distribution<> spd_dis(-5.0, 5.0);

	for (int i = 0; i < num_particles; i++)
	{
		Particle* p = new Particle(1, 1);

		double x_pos = dis(gen);
		double y_pos = dis(gen);
		double z_pos = dis(gen);

		double vx_rep = (coor_center.first + (x_pos * scale_factor));
		double vy_rep = (coor_center.second + (y_pos * scale_factor));

		double x_spd = spd_dis(gen);
		double y_spd = spd_dis(gen);
		double z_spd = spd_dis(gen);

		p->set_position(x_pos, y_pos, z_pos, vx_rep, vy_rep);
		p->set_speed(x_spd, y_spd, z_spd);

		particles.push_back(p);
	}
}

void Particle_System::update_projection(Particle* p)
{
	p->get_proy_position().position.x = (coor_center.first + (p->get_position().x * scale_factor) + (p->get_position().z * scale_factor * (0.5 * cos(camera_angle.z * PI / 180))));
	p->get_proy_position().position.y = (coor_center.second + (p->get_position().z * scale_factor) + (p->get_position().z * scale_factor * (0.5 * sin(camera_angle.z * PI / 180))));
}
