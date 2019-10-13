#ifndef ANIMATEDSPRITE_HPP
#define ANIMATEDSPRITE_HPP

#include <SFML/Graphics.hpp>
#include "graphics/animation.hpp"

namespace graphics{

class AnimatedSprite : public sf::Drawable {
    private:
        const Animation& animation;

        int currentFrame;
        sf::Time clock;


    public:
        sf::Sprite sprite;

        explicit AnimatedSprite(const Animation&);

        /** sf::Drawable implementaion **/
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

        /** update the frame to the current frame, called by update **/
        void updateSprite();

        void update(float);
};

}//namespace graphics

#endif