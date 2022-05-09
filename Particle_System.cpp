#include "Particle_System.h"

Particle_System::Particle_System(double space_size, double scale_factor, sf::RenderWindow& rw)
	:
	rw(rw),
	space_size(space_size),
	scale_factor(scale_factor),
	rx(RotMatrix::RotAxis::rx),
	ry(RotMatrix::RotAxis::ry),
	rz(RotMatrix::RotAxis::rz),
	gravitational_constant(6.67430 * (pow(10, -11))),
	PI(3.141592653)
{
	screen_size.first = rw.getSize().x;
	screen_size.second = rw.getSize().y;

	coor_center.first = screen_size.first / 2.0;
	coor_center.second = screen_size.second / 2.0;

	rotation.reset();
	camera_angle.reset();

	focal_point.x = coor_center.first;
	focal_point.z = coor_center.second;
	focal_point.y = (2.0) * (space_size);

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

		update_projection(p);

		update_attraction_forces(particles.back(), p);
		check_scapes(p);
	}

	clean_system();
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
		update_projection(p);
		//p->get_proy_position().position.x = (coor_center.first + (p->get_position().x * scale_factor));
		//p->get_proy_position().position.y = (coor_center.second + (p->get_position().z * scale_factor));
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
		update_projection(p);
		//p->get_proy_position().position.x = (coor_center.first + (p->get_position().x * scale_factor));
		//p->get_proy_position().position.y = (coor_center.second + (p->get_position().z * scale_factor));
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
		update_projection(p);
		//p->get_proy_position().position.x = (coor_center.first + (p->get_position().x * scale_factor));
		//p->get_proy_position().position.y = (coor_center.second + (p->get_position().z * scale_factor));
	}
}

void Particle_System::camera_x_rotate(double x)
{
	camera_angle.x += x;

	if (camera_angle.x >= 360.0)
	{
		camera_angle.x = camera_angle.x - 360.0;
	}

	//for (auto& p : particles)
	//{
	//	update_projection(p);
	//}
}

void Particle_System::camera_y_rotate(double y)
{
	camera_angle.y += y;

	if (camera_angle.y >= 360.0)
	{
		camera_angle.y = camera_angle.y - 360.0;
	}

	//for (auto& p : particles)
	//{
	//	update_projection(p);
	//}
}

void Particle_System::camera_z_rotate(double z)
{
	camera_angle.z += z;

	if (camera_angle.z >= 360.0)
	{
		camera_angle.z = camera_angle.z - 360.0;
	}

	//for (auto& p : particles)
	//{
	//	update_projection(p);
	//}
}

void Particle_System::generate_random_particles(int num_particles)
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<> dis(((-1) * (space_size / 2)) * 0.85, ((1) * (space_size / 2)) * 0.85);
	std::uniform_real_distribution<> spd_dis(-5.0, 5.0);

	for (int i = 0; i < num_particles; i++)
	{
		unsigned int id = particles.size() == 0 ? 0 : particles.back()->get_id() + 1;

		Particle* p = new Particle(1, 1, id, 0);

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

void Particle_System::generate_random_particles_nd(int num_particles)
{
	double sdfcr = 0.45; //start_distance_from_center_ratio

	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<> dis_x(((-1) * (space_size / 2)) * sdfcr, ((1) * (space_size / 2)) * sdfcr);
	std::uniform_real_distribution<> dis_y(((-1) * (space_size / 2)) * sdfcr, ((1) * (space_size / 2)) * sdfcr);
	std::normal_distribution<> dis_z(0, space_size * 0.02);
	std::uniform_real_distribution<> spd_dis(10000, 100000.0);
	std::uniform_real_distribution<> spd_dis_z(-2.0, 2.0);

	for (int i = 0; i < num_particles; i++)
	{
		unsigned int id = particles.size() == 0 ? 0 : particles.back()->get_id() + 1;

		Particle* p = new Particle(1.0*pow(10,4), 1, id, 0);

		double x_pos = dis_x(gen);
		//double y_pos = dis_y(gen);
		//double z_pos = dis_z(gen);
		double z_pos = dis_y(gen);
		double y_pos = dis_z(gen);

		double vx_rep = (coor_center.first + (x_pos * scale_factor));
		double vy_rep = (coor_center.second + (y_pos * scale_factor));

		double spd = spd_dis(gen);

		//double r = sqrt((x_pos * x_pos) + (y_pos * y_pos));
		double r = sqrt((x_pos * x_pos) + (z_pos * z_pos));

		double cs = cos(acos(x_pos / r)+(PI/2.0));
		/*double sn = y_pos / r;*/
		double sn = sin(asin(z_pos / r)+(PI/2.0));

		double x_spd = spd * cs;
		/*double y_spd = spd * sn;*/
		double z_spd = spd * sn;

		/*double z_spd = spd_dis_z(gen);*/
		double y_spd = spd_dis_z(gen);

		p->set_position(x_pos, y_pos, z_pos, vx_rep, vy_rep);
		p->set_speed(x_spd, y_spd, z_spd);

		particles.push_back(p);
	}
}

void Particle_System::generate_particle(double mass, double radius, Vertex3D pos, Vertex3D speed, bool fixed)
{
	unsigned int id = particles.size() == 0 ? 0 : particles.back()->get_id() + 1;

	Particle* p = new Particle(mass, radius, id, fixed);

	p->set_speed(speed.x, speed.y, speed.z);
	p->set_position(pos.x, pos.y, pos.z, 0, 0);

	update_projection(p);

	particles.push_back(p);
}

void Particle_System::update_attraction_forces(Particle* q,Particle* p)
{
	double dx = 0.0;
	double dy = 0.0;
	double dz = 0.0;

	double dt = 0.0;
	double ft = 0.0;

	double ca = 0.0;
	double saz = 0.0;
	double sa = 0.0;

	Vertex3D f;

	if (p->get_id() != q->get_id())
	{
		dx = (p->get_position().x - q->get_position().x);
		dy = (p->get_position().y - q->get_position().y);
		dz = (p->get_position().z - q->get_position().z);

		dt = sqrt((dx * dx) + (dy * dy) + (dz * dz));

		if (dt < p->get_radius() + q->get_radius())
		{
			p->toggle_state();
		}
		else
		{
			ca = dx / dt;
			sa = dy / dt;
			saz = dz / dt;

			ft = (-1.0) * gravitational_constant * (p->get_mass() * q->get_mass()) / (dt * dt);

			f.x = ca * ft;
			f.y = sa * ft;
			f.z = saz * ft;

			p->set_force(f);
		}
	}
}

void Particle_System::check_scapes(Particle * p)
{
	if (sqrt((p->get_position().x * p->get_position().x) + (p->get_position().y * p->get_position().y) + p->get_position().z * p->get_position().z) >= (space_size / 2.0))
	{
		p->toggle_state();
	}
}

void Particle_System::clean_system()
{
	int idx = 0;

	while (idx < particles.size())
	{
		idx = 0;

		for (int i = 0; i < particles.size(); i++)
		{
			if (!particles[i]->get_state())
			{
				particles.erase(particles.begin() + i);

				break;
			}

			idx++;
		}
	}

}

void Particle_System::update_projection(Particle* p)
{
	double deep = std::abs(focal_point.y + p->get_position().y) / focal_point.y;

	//cube[va] = sf::Vector2f(focal_point.x + ((std::abs(deep) * space_vertex[idx].x) * scale_factor), focal_point.z + ((std::abs(deep) * space_vertex[idx].z) * scale_factor));
	//cube[vb] = sf::Vector2f(focal_point.x + ((std::abs(deep) * space_vertex[idx].x) * scale_factor), focal_point.z + ((std::abs(deep) * space_vertex[idx].z) * scale_factor));
	//cube[vc] = sf::Vector2f(focal_point.x + ((std::abs(deep) * space_vertex[idx].x) * scale_factor), focal_point.z + ((std::abs(deep) * space_vertex[idx].z) * scale_factor));

	p->get_proy_position().position.x = (focal_point.x + ((p->get_position().x * std::abs(deep)) * scale_factor));
	p->get_proy_position().position.y = (focal_point.z + ((p->get_position().z * std::abs(deep)) * scale_factor));
}
