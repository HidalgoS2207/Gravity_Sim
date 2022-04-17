#pragma once

#include "Sim_Core.h"

#include <SFML/Graphics.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 800), "Gravity Sim");

    Sim_Core sim_core(window);

    sf::Clock sim_clock;
    float sim_clock_rate = 0.001;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        while (sim_clock.getElapsedTime().asMilliseconds() < sim_clock_rate)
        {
            sim_core.update();
        }

        window.clear();

        sim_core.draw();

        window.display();

        sim_clock.restart();
    }

    return 0;
}