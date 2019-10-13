#ifndef ANIMATION_HPP
#define ANIMATION_HPP

#include <SFML/Graphics.hpp>

namespace graphics{

class Animation {
    public:
        const sf::Texture& texture;
        const int nbFrames;
        const sf::Time frameTime;
        const bool loop;

        const int height;
        const int width;
        const int offset_h;
        const int offset_w;

        /** Constructor : width, height of a sprite, then offsetw, offseth then nb frame then isLoop**/
        explicit Animation(int,int,int,int,const sf::Texture&,int,sf::Time _fT=sf::seconds(0.1),bool _loop=true);      

};

}

#endif