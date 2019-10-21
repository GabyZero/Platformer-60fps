#include "block.hpp"

Block::Block()
{
    //sprite->setScale(_TILE_WIDTH/width,_TILE_HEIGHT/height); 
}

Block::Block(sf::IntRect& rect,const sf::Texture &text)
{   
    sprite = new sf::Sprite(text, rect);
    sprite->setScale(_TILE_WIDTH/rect.width,_TILE_HEIGHT/rect.height); 
}

Block::~Block()
{
    delete sprite;
}

void Block::setPosition(float x, float y)
{
    sprite->setPosition(x,y);
}

void Block::update(float)
{
    //do nothing
}

void Block::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(*sprite, states);
}

/** ICollidable implementation **/
void Block::collisionEnter(const ICollidable &, sf::FloatRect )
{

}

const sf::Vector2f& Block::getPosition() const
{
    return sprite->getPosition();
}

sf::FloatRect Block::getGlobalBounds() const
{
    return sprite->getGlobalBounds();
}

/** end icollidable **/