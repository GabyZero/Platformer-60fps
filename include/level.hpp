#ifndef LEVEL_HPP
#define LEVEL_HPP

#include <vector>
#include <SFML/Graphics.hpp>
#include <physics/icollidable.hpp>

class Game;

class Level : public sf::Drawable{
    private:
        Game &game;
    public:
        std::vector<physics::ICollidable*> collidable;

        std::vector<sf::Sprite> others;

        Level(Game&);
        ~Level();

        void loadMap(const std::string path);
        void initLevel();

        void update(const double);
        void updatePhysics(const double);

        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
        
};

#endif