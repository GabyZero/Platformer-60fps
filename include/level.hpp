#ifndef LEVEL_HPP
#define LEVEL_HPP

#include <vector>
#include <SFML/Graphics.hpp>
#include <physics/icollidable.hpp>

class Level : public sf::Drawable{
    public:
        std::vector<physics::ICollidable*> collidable;

        std::vector<sf::Sprite> others;

        Level();
        ~Level();

        void loadMap(const std::string path);
        void initLevel();

        void update(const double);
        void updatePhysics(const double);

        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
        
};

#endif