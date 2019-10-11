#include "graphics/staticbackground.hpp"

#include "game.hpp"

#include <iostream>

namespace  graphics{

StaticBackground::StaticBackground()
{
    sprite.setPosition(_CAMERA_WIDTH*-1,_CAMERA_HEIGHT*-1);
}

void StaticBackground::setImage(const sf::Texture &texture)
{
    sprite.setTexture(texture,true);
}

void StaticBackground::setSize(const int &height, const int &width)
{
    sprite.setTextureRect(sf::IntRect(0,0,height,width));
}

void StaticBackground::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(sprite, states);
    std::cout << "test : " << sprite.getTextureRect().top << " " << sprite.getTextureRect().left << std::endl;
}

StaticBackground::~StaticBackground()
{

}

} // namespace  graphic


