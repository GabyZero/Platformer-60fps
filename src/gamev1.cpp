#include "gamev1.hpp"

#include <iostream>

Gamev1::Gamev1():Game()
{}

Gamev1::~Gamev1(){}

void Gamev1::run()
{
    _Float32 dt = 1.0f / 60.0f; 
    sf::Clock clock;

    sf::Time begin = clock.getElapsedTime();
    bool paused = false;

    window.setFramerateLimit(62);
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::C)) paused = true;
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) paused = false;
        if(!paused)
        {
            window.clear();

            scene.update(dt);
            scene.updatePhysics(1.0f / 60.0f);

            scene.render(window);
        
        
        
            window.display();
        }

        sf::Time end = clock.getElapsedTime();
        dt = (end-begin).asSeconds();

        begin = end;

        //std::cout << 1.0f/dt << std::endl;
    }
}