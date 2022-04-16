#include "Sim_Core.h"

Sim_Core::Sim_Core(sf::RenderWindow& rw)
	:
	rw(rw),
	tic(0.001),
	rot_stps(0.001),
	gravitational_constant(6.67430 * (pow(10, -11))),
	space({ rw.getSize().x,rw.getSize().y }, 3000)
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
}

Sim_Core::~Sim_Core()
{}

void Sim_Core::update()
{
	kbd_input();
	space.update();
}

void Sim_Core::draw()
{
	space.draw(rw);

	for (int i = 0; i < signs.size(); i++)
	{
		rw.draw(signs[i]);
	}
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
		signs[2].setString(std::to_string(space.get_rotation_z()));
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Y))
	{
		space.y_rotate(rot_stps);
		signs[1].setString(std::to_string(space.get_rotation_y()));
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::X))
	{
		space.x_rotate(rot_stps);
		signs[0].setString(std::to_string(space.get_rotation_x()));
	}
}
