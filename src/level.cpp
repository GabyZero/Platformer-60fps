#include "level.hpp"

#include "resources/resourcesmanager.hpp"
#include <iostream>

Level::Level()
{}

void Level::initLevel()
{
    sf::Sprite sprite(resources::ResourcesManager::instance().textures.getAsset("block"));
    sprite.setPosition(255,200);
    collidable.push_back(std::move(sprite));

    sprite = sf::Sprite(sprite);
    sprite.setPosition(255,280);
    collidable.push_back(std::move(sprite));

    sprite = sf::Sprite(sprite);
    sprite.setPosition(350,255);
    collidable.push_back(std::move(sprite));

    sprite = sf::Sprite(sprite);
    sprite.setPosition(150,255);
    collidable.push_back(std::move(sprite));
    
    //** todo: ajout de 4 gros collidable autour du niveau
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