#include "block.hpp"

Block::Block()
{
    //sprite->setScale(_TILE_WIDTH/width,_TILE_HEIGHT/height); 
}

Block::Block(sf::IntRect& rect,const sf::Texture &text,bool scalable)
{   
    sprite = new sf::Sprite(text, rect);
    if(scalable) sprite->setScale(_TILE_WIDTH/rect.width,_TILE_HEIGHT/rect.height); 
}

void Block::setScale(float f1,float f2)
{
    sprite->setScale(f1/getGlobalBounds().width, f2/getGlobalBounds().height );
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
/*void Block::verticalCollisionEnter(const ICollidable &)
{

}

void Block::horizontalCollisionEnter(const ICollidable &)
{

}*/
void Block::collisionEnter(const ICollidable &, sf::FloatRect)
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