#include "gamev1.hpp"

#include <iostream>

Gamev1::Gamev1():Game()
{}

Gamev1::~Gamev1(){}

#include "graphics/animatedsprite.hpp"
#include "resources/resourcesmanager.hpp"

void Gamev1::run()
{
    _Float32 dt = 1.0f / _FPS; 
    sf::Clock clock;

    sf::Time begin = clock.getElapsedTime();
    bool paused = false;

    window.setFramerateLimit(_FPS+2);

    graphics::AnimatedSprite test(resources::ResourcesManager::instance().animations.getAsset("fire"));
    test.sprite.setPosition(scene.player.getPosition()+sf::Vector2f{20,0});

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
            test.update(dt);
            scene.updatePhysics(1.0f / _FPS);

            view.setCenter(scene.player.getPosition());
            window.setView(view);

            scene.render(window);
            window.draw(test); 
            window.display();
        }

        sf::Time end = clock.getElapsedTime();
        dt = (end-begin).asSeconds();

        begin = end;

        std::cout << 1.0f/dt << std::endl;
    }
}