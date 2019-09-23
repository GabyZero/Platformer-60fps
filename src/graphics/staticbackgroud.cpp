#include "graphics/staticbackground.hpp"

namespace  graphics{

StaticBackground::StaticBackground()
{

}

StaticBackground::StaticBackground(std::string _path):
texture(),sprite()
{
    setImage(_path);
}

void StaticBackground::setImage(std::string path)
{
    if(!texture.loadFromFile(path))
    {
        //throw "backgroud not found";
    }
    else
    {
        sprite.setTexture(texture,true);
    }
}

void StaticBackground::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(sprite, states);
}

StaticBackground::~StaticBackground()
{

}

} // namespace  graphic


