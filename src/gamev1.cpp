#include "gamev1.hpp"

#include <iostream>

Gamev1::Gamev1():Game()
{}

void Gamev1::run()
{
    _Float32 dt = 1.0f / 60.0f; 
    sf::Clock clock;

    sf::Time begin = clock.getElapsedTime();

    window.setFramerateLimit(60);
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();


        scene.update(dt);
        scene.updatePhysics(1.0f / 60.0f);

        scene.render(window);
        
        
        window.display();

        sf::Time end = clock.getElapsedTime();
        dt = (end-begin).asSeconds();

        begin = end;

        //std::cout << 1.0f/dt << std::endl;
    }
}