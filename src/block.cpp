#include "block.hpp"

Block::Block(sf::IntRect& rect,const sf::Texture &text):
sprite(text, rect)
{
    sprite.setScale(_TILE_WIDTH/rect.width,_TILE_HEIGHT/rect.height);
    
}

void Block::setPosition(float x, float y)
{
    sprite.setPosition(x,y);
}


void Block::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(sprite, states);
}

/** ICollidable implementation **/
void Block::collisionEnter(const ICollidable &collidable, sf::FloatRect collision)
{

}

const sf::Vector2f& Block::getPosition() const
{
    return sprite.getPosition();
}

sf::FloatRect Block::getGlobalBounds() const
{
    return sprite.getGlobalBounds();
}

/** end icollidable **/