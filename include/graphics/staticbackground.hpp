#ifndef STATICBACKGROUND_HPP
#define STATICBACKGROUND_HPP

#include <SFML/Graphics.hpp>

namespace graphics
{
    /** Backgroud of the game **/
    class StaticBackground : public sf::Drawable
    {
        private:
            sf::Sprite sprite;

        public:
            StaticBackground();

            /** set image the image of the background, shall be the size of the game **/
            void setImage(const sf::Texture&);

            /** sf::Drawable implementaion **/
            virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

            ~StaticBackground();
    };
}

#endif