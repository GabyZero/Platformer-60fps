#include "gamev1.hpp"

#include <iostream>

#define FPS 10.0f

Gamev1::Gamev1():Game()
{}

Gamev1::~Gamev1(){}

void Gamev1::run()
{
<<<<<<< HEAD
    _Float32 dt = 1.0f / _FPS; 
=======
    _Float32 dt = 1.0f / FPS; 
>>>>>>> 5d62783e50e2508290b7a29404b93b5660677d7c
    sf::Clock clock;

    sf::Time begin = clock.getElapsedTime();
    bool paused = false;

<<<<<<< HEAD
    window.setFramerateLimit(_FPS+2);
=======
    window.setFramerateLimit(FPS);
>>>>>>> 5d62783e50e2508290b7a29404b93b5660677d7c
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

        if(!paused)
        {
            window.clear();

            scene.update(dt);
<<<<<<< HEAD
            scene.updatePhysics(1.0f / _FPS);
=======
            scene.updatePhysics(1.0f / FPS);
>>>>>>> 5d62783e50e2508290b7a29404b93b5660677d7c

            view.setCenter(scene.player.getPosition());
            window.setView(view);

            scene.render(window);    
            window.display();
        }

        sf::Time end = clock.getElapsedTime();
        dt = (end-begin).asSeconds();

        begin = end;

        std::cout << 1.0f/dt << std::endl;
    }
}