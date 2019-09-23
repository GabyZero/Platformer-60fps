#ifndef SCENE_HPP
#define SCENE_HPP

#include "sceneinterface.hpp"
#include "graphics/staticbackground.hpp"
#include <forward_list>

class Scene : public SceneInterface{
    private:
        //std::forward_list<std::sf::Drawable> static_elements;
         graphics::StaticBackground background;

    public:
        Scene();

        void initScene();
        virtual void render(sf::RenderWindow &window);

        ~Scene();
};

#endif