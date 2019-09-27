#include "level.hpp"

Level::Level()
{}

void Level::initLevel()
{
    
}

void Level::update(double dt)
{

}

void Level::updatePhysics(double dt)
{

}

void Level::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    for(sf::Sprite sp : collidable)
        target.draw(sp, states);

    for(sf::Sprite sp : others)
        target.draw(sp, states);
}