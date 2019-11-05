#ifndef ANIMATION_HPP
#define ANIMATION_HPP

#include <SFML/Graphics.hpp>

namespace graphics{

struct Animation {
        const sf::Texture& texture;
        const sf::Vector2i nbFrames;
        const sf::Time frameTime;
        const bool loop;

        const int height;
        const int width;
        const int offset_h;
        const int offset_w;

        /** Constructor : width, height of a sprite, then offsetw, offseth then nb frame then isLoop**/
        explicit Animation(const int,const int,const int,const int,const sf::Texture&,const sf::Vector2i,sf::Time _fT=sf::seconds(0.1),const bool _loop=true);      

};

}

#endif