#include "scene.hpp"

#include "resources/resourcesmanager.hpp"

Scene::Scene()
{

}

void Scene::initScene()
{
    background.setImage(resources::ResourcesManager::instance().textures.getAsset("background"));
    player.initPlayer();
    level.initLevel();
}

#include <iostream>

void Scene::manageCollisions()
{
    sf::FloatRect rectP = player.sprite.getGlobalBounds();
    sf::FloatRect rectTmp;
    for(const sf::Sprite &sp : level.collidable) //todo: don't test * //
    {
        //std::cout << sp.getGlobalBounds().height << " " << sp.getGlobalBounds().width << std::endl;
        if(rectP.intersects(sp.getGlobalBounds(),rectTmp))
        {
            std::cout << rectTmp.left << " " << rectTmp.top << " " <<
            rectTmp.height << " " << rectTmp.width << std::endl;
            
            //top or down
            if(rectTmp.top == sp.getPosition().y && player.yAcceleration <.0f) //is the player falling ?
            {
                player.sprite.setPosition(player.sprite.getPosition() + sf::Vector2(.0f,rectTmp.height*-1));
                player.yAcceleration = .0f;
                continue;
            }
            else if(player.yAcceleration>.0f) //is the player jumping ?
            {
                player.sprite.setPosition(player.sprite.getPosition() + sf::Vector2(.0f,rectTmp.height));
                player.yAcceleration = -.1f;
                continue;
            }

            //left or right 
            if(rectTmp.left == sp.getPosition().x) //from the left
            {
                player.sprite.setPosition(player.sprite.getPosition() + sf::Vector2(rectTmp.width*-1,.0f));
                continue;
            }
            else
            {
                player.sprite.setPosition(player.sprite.getPosition() + sf::Vector2(rectTmp.width,.0f));
                continue;
            }
            
        }
    } 
}

void Scene::updatePhysics(_Float32 dt)
{
    player.updatePhysics(dt);
    level.updatePhysics(dt);

    manageCollisions();
}

void Scene::update(float dt)
{
    player.update(dt);
    level.update(dt);
}

void Scene::render(sf::RenderWindow& window)
{
    window.draw(background);
    window.draw(level);
    window.draw(player);
}

Scene::~Scene()
{

}