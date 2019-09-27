#include "gamev1.hpp"

#include <iostream>
#include <chrono>

Gamev1::Gamev1():Game()
{}

void Gamev1::run()
{
    _Float32 dt = 1.0f / 60.0f; 
    std::chrono::duration<_Float32> tmp_dt;

    std::chrono::time_point begin_ticks = std::chrono::high_resolution_clock::now();
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();


        scene.player.Update(dt);
        scene.UpdatePhysics(1.0f / 60.0f);

        scene.render(window);
        
        
        window.display();

        std::chrono::time_point end_ticks = std::chrono::high_resolution_clock::now();
        tmp_dt = std::chrono::duration_cast<std::chrono::duration<_Float32>>(end_ticks-begin_ticks);


        dt = tmp_dt.count();

        begin_ticks = end_ticks;

        std::cout << 1.0f/dt << std::endl;
    }
}