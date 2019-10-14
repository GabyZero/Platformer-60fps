#ifndef ANIMATEDSPRITE_HPP
#define ANIMATEDSPRITE_HPP

#include <SFML/Graphics.hpp>
#include "graphics/animation.hpp"

namespace graphics{

class AnimatedSprite : public sf::Sprite{
    private:
        const Animation& animation;

        int currentFrame;
        sf::Time clock;


    public:
        explicit AnimatedSprite(const Animation&);

        /** update the frame to the current frame, called by update **/
        void updateSprite();

        void update(float);
};

}//namespace graphics

#endif