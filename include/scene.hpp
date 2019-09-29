#ifndef SCENE_HPP
#define SCENE_HPP

#include "sceneinterface.hpp"
#include "graphics/staticbackground.hpp"
#include "player.hpp"
#include "level.hpp"

#include <forward_list>

class Scene : public SceneInterface{
    public:
        //std::forward_list<std::sf::Drawable> static_elements;
        graphics::StaticBackground background;
        Player player;

        Level level;


        Scene();

        void initScene();
        void manageCollisions();
        void updatePhysics(_Float32);
        void update(float);
        virtual void render(sf::RenderWindow &window);

        ~Scene();
};

#endif