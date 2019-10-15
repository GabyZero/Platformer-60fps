#include "gamev1.hpp"

#include <iostream>

<<<<<<< HEAD
#define FPS 120.0f

=======
>>>>>>> 0944dd818171efc47b9ca93a3b7e9682eddb58e3
Gamev1::Gamev1():Game()
{}

Gamev1::~Gamev1(){}

void Gamev1::run()
{
    _Float32 dt = 1.0f / _FPS; 
    sf::Clock clock;

    bool paused = false;

<<<<<<< HEAD
    int fpf = 0;

    window.setFramerateLimit(FPS);
=======
    window.setFramerateLimit(_FPS+2);
    
    sf::Time begin = clock.getElapsedTime();
>>>>>>> 0944dd818171efc47b9ca93a3b7e9682eddb58e3
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::C)) paused = true;
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::V)) paused = false;
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) break;
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::B)) fpf=0;
        if(!paused && fpf<1)
        {
            //fpf++;
            window.clear();

            scene.update(dt);
            scene.updatePhysics(1.0f / _FPS);

            view.setCenter(scene.player.getPosition());
            window.setView(view);

            scene.render(window);
            window.display();
        }

        sf::Time end = clock.getElapsedTime();
        dt = (end-begin).asSeconds();

        begin = end;
<<<<<<< HEAD
        //paused = true;
        //std::cout << 1.0f/dt << std::endl;
=======

        std::cout << 1.0f/dt << std::endl;
>>>>>>> 0944dd818171efc47b9ca93a3b7e9682eddb58e3
    }
}