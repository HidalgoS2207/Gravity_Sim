#include "Sim_Core.h"

Sim_Core::Sim_Core(sf::RenderWindow& rw)
	:
	rw(rw),
	tic(0.5),
	rot_stps(0.1),
	gravitational_constant(6.67430 * (pow(10, -11))),
	space({ rw.getSize().x,rw.getSize().y }, 1.0*pow(10,8)),
	particle_system(space.get_size(), space.get_scale_factor(),rw)
{
	std::cout << gravitational_constant << '\n';

	font1.loadFromFile("Assets/Kufam-Regular.ttf");
	font2.loadFromFile("Assets/Kufam-VariableFont_wght.ttf");

	//-----------------------------------------------------------------------------

	signs.emplace_back();
	set_sign(font1, signs[0], "0.0", 15, rw.getSize().x - 100, rw.getSize().y - 60);

	signs.emplace_back();
	set_sign(font1, signs[1], "0.0", 15, rw.getSize().x - 100, rw.getSize().y - 40);

	signs.emplace_back();
	set_sign(font1, signs[2], "0.0", 15, rw.getSize().x - 100, rw.getSize().y - 20);

	signs.emplace_back();
	set_sign(font1, signs[3], "0.0", 15, rw.getSize().x - 200,  20);

	//------------------------------------------------------------------------------

	Vertex3D p_pos;
	p_pos.x = 100.0;
	p_pos.y = 100.0;
	p_pos.z = 100.0;
	Vertex3D p_spd;
	p_spd.x = 0.0;
	p_spd.y = 0.0;
	p_spd.z = 0.0;

	//particle_system.generate_particle(100, 10, p_pos, p_spd,false);

	p_pos.x = 0.0;
	p_pos.y = 0.0;
	p_pos.z = 0.0;

	p_spd.x = 0.0;
	p_spd.y = 0.0;
	p_spd.z = 0.0;

	particle_system.generate_random_particles_nd(15000);

	particle_system.generate_particle(5.97 * pow(10, 24), 3 * pow(10, 6), p_pos, p_spd, true);
}

Sim_Core::~Sim_Core()
{}

void Sim_Core::update()
{
	kbd_input();
	//space.update();
	particle_system.update(tic);

	signs[3].setString("Particles Count: " + std::to_string(particle_system.get_num_particles()));
}

void Sim_Core::draw()
{
	for (int i = 0; i < signs.size(); i++)
	{
		rw.draw(signs[i]);
	}

	particle_system.draw();
	//space.draw(rw);
}

void Sim_Core::set_sign(sf::Font& font, sf::Text& to, std::string text, int size, int x_pos, int y_pos)
{
	to.setFont(font);
	to.setCharacterSize(size);
	to.setPosition(x_pos, y_pos);
	to.setString(text);
}

void Sim_Core::kbd_input()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) || sf::Keyboard::isKeyPressed(sf::Keyboard::RShift))
		{
			particle_system.z_rotate(rot_stps*(-1.0));
			particle_system.camera_x_rotate(rot_stps * (-1.0));
			signs[2].setString(std::to_string(particle_system.get_rotation().z));
		}
		else
		{
			particle_system.z_rotate(rot_stps);
			particle_system.camera_x_rotate(rot_stps);
			signs[2].setString(std::to_string(particle_system.get_rotation().z));
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Y))
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) || sf::Keyboard::isKeyPressed(sf::Keyboard::RShift))
		{
			particle_system.y_rotate(rot_stps*(-1.0));
			particle_system.camera_y_rotate(rot_stps*(-1.0));
			signs[1].setString(std::to_string(particle_system.get_rotation().y));
		}
		else
		{
			particle_system.y_rotate(rot_stps);
			particle_system.camera_y_rotate(rot_stps);
			signs[1].setString(std::to_string(particle_system.get_rotation().y));
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::X))
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) || sf::Keyboard::isKeyPressed(sf::Keyboard::RShift))
		{
			particle_system.x_rotate(rot_stps*(-1.0));
			particle_system.camera_z_rotate(rot_stps*(-1.0));
			signs[0].setString(std::to_string(particle_system.get_rotation().x));
		}
		else
		{
			particle_system.x_rotate(rot_stps);
			particle_system.camera_z_rotate(rot_stps);
			signs[0].setString(std::to_string(particle_system.get_rotation().x));
		}
	}
}
