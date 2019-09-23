#ifndef SCENEINTERFACE_HPP
#define SCENEINTERFACE_HPP

#include <SFML/Graphics.hpp>

class SceneInterface{
    public:
        virtual void render(sf::RenderWindow& window) = 0;
};

#endif