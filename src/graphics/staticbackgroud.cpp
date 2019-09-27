#include "graphics/staticbackground.hpp"

namespace  graphics{

StaticBackground::StaticBackground()
{

}


void StaticBackground::setImage(const sf::Texture &texture)
{

    sprite.setTexture(texture,true);
    
}

void StaticBackground::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(sprite, states);
}

StaticBackground::~StaticBackground()
{

}

} // namespace  graphic


