#ifndef SCENE_HPP
#define SCENE_HPP

#include "sceneinterface.hpp"
#include "graphics/staticbackground.hpp"
#include "player.hpp"
#include "level.hpp"
#include "physics/icollidable.hpp"

#include <forward_list>

class Game;

class Scene : public SceneInterface{
    private:
        Game& game;
    public:
        graphics::StaticBackground background;
        Player player;

        Level level;


        Scene(Game &game);

        void initScene();
        void managePlayerCollisions(float);
        void updatePhysics(_Float32);
        void update(float);
        virtual void render(sf::RenderWindow &window);

        ~Scene();
};

#endif