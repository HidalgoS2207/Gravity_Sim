#pragma once

#include <SFML/Graphics.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 800), "Gravity Sim");

    sf::Clock sim_clock;
    float sim_clock_rate = 2.0;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();

        while (sim_clock.getElapsedTime().asMilliseconds() < sim_clock_rate)
        {

        }

        window.display();
    }

    return 0;
}