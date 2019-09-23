#ifndef STATICBACKGROUND_HPP
#define STATICBACKGROUND_HPP

#include <SFML/Graphics.hpp>

namespace graphics
{
    /** Backgroud of the game **/
    class StaticBackground : public sf::Drawable
    {
        private:
            sf::Texture texture;
            sf::Sprite sprite;

        public:
            StaticBackground();
            StaticBackground(std::string);

            /** set image the image of the background, shall be the size of the game **/
            void setImage(std::string);

            /** sf::Drawable implementaion **/
            virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

            ~StaticBackground();
    };
}

#endif