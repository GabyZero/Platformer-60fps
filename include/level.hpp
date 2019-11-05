#ifndef LEVEL_HPP
#define LEVEL_HPP

#include <vector>
#include <SFML/Graphics.hpp>
#include "physics/icollidable.hpp"

class Game;

class Level : public sf::Drawable{
    private:
        Game &game;
    public:
        std::vector<physics::ICollidable*> collidable;
        std::vector<physics::ICollidable*> trigerrable;

        enum LevelOther{CASTLE,EXPLOSION,LOCOUNT};
        physics::ICollidable** others;

        sf::FloatRect globalBounds;

        sf::Thread switchlevel;

        Level(Game&);
        ~Level();

        void loadMap(const std::string path);
        void initLevel();
        bool initLevel(int);
        void switchLevel();
        void update(const double);
        void updatePhysics(const double);

        void endLevel(int newlevel);

        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
        
};


#endif