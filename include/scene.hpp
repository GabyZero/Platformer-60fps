#ifndef SCENE_HPP
#define SCENE_HPP

#include "sceneinterface.hpp"
#include "graphics/staticbackground.hpp"
#include "player.hpp"

#include <forward_list>

class Scene : public SceneInterface{
    public:
        //std::forward_list<std::sf::Drawable> static_elements;
        graphics::StaticBackground background;
        Player player;


        Scene();

        void initScene();
        void UpdatePhysics(_Float32);
        virtual void render(sf::RenderWindow &window);

        ~Scene();
};

#endif