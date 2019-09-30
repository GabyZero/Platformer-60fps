#ifndef LEVEL_HPP
#define LEVEL_HPP

#include <vector>
#include <SFML/Graphics.hpp>

class Level : public sf::Drawable{
    public:
        std::vector<sf::Sprite> collidable;

        std::vector<sf::Sprite> others;

        Level();

        void loadMap(const std::string path);
        void initLevel();

        void update(const double);
        void updatePhysics(const double);

        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
        
};

#endif