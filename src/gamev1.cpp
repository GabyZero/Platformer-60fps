#include "gamev1.hpp"

Gamev1::Gamev1():Game()
{}

void Gamev1::run()
{
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();

        scene.render(window);

        window.display();
    }
}