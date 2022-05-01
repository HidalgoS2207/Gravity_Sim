#include "Sim_Core.h"

Sim_Core::Sim_Core(sf::RenderWindow& rw)
	:
	rw(rw),
	tic(0.01),
	rot_stps(0.001),
	gravitational_constant(6.67430 * (pow(10, -11))),
	space({ rw.getSize().x,rw.getSize().y }, 15000),
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

	//------------------------------------------------------------------------------

	particle_system.generate_random_particles(5);
}

Sim_Core::~Sim_Core()
{}

void Sim_Core::update()
{
	kbd_input();
	//space.update();
	particle_system.update(tic);
}

void Sim_Core::draw()
{
	for (int i = 0; i < signs.size(); i++)
	{
		rw.draw(signs[i]);
	}

	particle_system.draw();
	space.draw(rw);
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
		space.z_rotate(rot_stps);
		particle_system.z_rotate(rot_stps);
		//particle_system.camera_x_rotate(rot_stps);
		signs[2].setString(std::to_string(space.get_rotation_z()));
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Y))
	{
		space.y_rotate(rot_stps);
		particle_system.y_rotate(rot_stps);
		//particle_system.camera_y_rotate(rot_stps);
		signs[1].setString(std::to_string(space.get_rotation_y()));
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::X))
	{
		space.x_rotate(rot_stps);
		particle_system.x_rotate(rot_stps);
		//particle_system.camera_z_rotate(rot_stps);
		signs[0].setString(std::to_string(space.get_rotation_x()));
	}
}
