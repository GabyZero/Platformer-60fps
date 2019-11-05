#include "movingblock.hpp"

MovingBlock::MovingBlock(sf::IntRect &rect, const sf::Texture &text,int nbblocmove,sf::Vector2f accel):
Block(rect,text)
{
    nbBloc = nbblocmove;
    acceleration = accel;
}

void MovingBlock::update(float dt)
{
    if(std::max(std::abs(getPosition().x-defaultposition.x),std::abs(getPosition().y-defaultposition.y))>(nbBloc*_TILE_HEIGHT))
    {
        acceleration.x = acceleration.x * -1;
        acceleration.y = acceleration.y * -1;
    }
}

void MovingBlock::updatePhysics(float dt)
{
    sprite->setPosition(getPosition()+ (acceleration*dt));
}

void MovingBlock::setPosition(float x, float y)
{
    defaultposition = {x,y};
    Block::setPosition(x,y);
}
