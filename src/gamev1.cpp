#include "gamev1.hpp"

#include <iostream>


Gamev1::Gamev1():Game()
{}

Gamev1::~Gamev1(){}

void Gamev1::run()
{
    std::cout << "Launching game loop" << std::endl;
    
    _Float32 dt = 1.0f / _FPS; 
    sf::Clock clock;


    //window.setFramerateLimit(_FPS+2);

    audioManager.start();
    
    sf::Time begin = clock.getElapsedTime();
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
                
        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) break;
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Return)) Game::setPause(false); //debug
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) && sf::Keyboard::isKeyPressed(sf::Keyboard::M)) audioManager.setMute(false);
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::M)){audioManager.setMute(true);}
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::L)) {scene.level.endLevel(level);/*scene.level.switchlevel.launch();*/}
        if(!pause)
        {
            window.clear();

            manageEvents();

            scene.update(dt);
            scene.updatePhysics(dt);
            ui.update(dt);

            view.setCenter(scene.player.getPosition());
            audioManager.setCenter(scene.player.getPosition());

            window.setView(view);

            scene.render(window);
            ui.render(window);
            window.display();
            //std::cout <<std::endl<< "NEW FRAME" << std::endl << std::endl;
            //setPause(true);

        }

        sf::Time end = clock.getElapsedTime();
        dt = (end-begin).asSeconds();

        begin = end;
        std::cout << 1.0f/dt << std::endl;
    }
}