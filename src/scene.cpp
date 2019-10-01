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

/** return true if the collision test is relevent **/
bool isCollisionTestRelevent(const sf::FloatRect &player, const sf::FloatRect &collidable)
{
    return true;
}

#include <iostream>

void Scene::managePlayerCollisions()
{
    sf::FloatRect rectP = player.sprite.getGlobalBounds();
    sf::FloatRect rectTmp;
    for(const sf::Sprite &sp : level.collidable) //todo: don't test * //
    {
        if(!isCollisionTestRelevent(rectP, sp.getGlobalBounds())) continue;

        //std::cout << sp.getGlobalBounds().height << " " << sp.getGlobalBounds().width << std::endl;
        if(rectP.intersects(sp.getGlobalBounds(),rectTmp))
        {
            std::cout << rectTmp.left << " " << rectTmp.top << " " <<
            rectTmp.height << " " << rectTmp.width << std::endl;
            if(rectTmp.width>rectTmp.height)
            {
                //top or down
                if(rectTmp.top == sp.getPosition().y && player.yAcceleration <.0f) //is the player falling ?
                {
                    player.sprite.setPosition(player.sprite.getPosition() + sf::Vector2(.0f,rectTmp.height*-1));
                    player.yAcceleration = .0f;
                    rectP = player.sprite.getGlobalBounds();
                    continue;
                }
                else if(player.yAcceleration>.0f /*&& rectP.top-rectTmp.top > 16/2*/) //is the player jumping ?
                {
                    player.sprite.setPosition(player.sprite.getPosition() + sf::Vector2(.0f,rectTmp.height));
                    player.stopJumping();
                    rectP = player.sprite.getGlobalBounds();
                    continue;
                }
            }
            else
            {
                //left or right 
                if(rectTmp.left == sp.getPosition().x) //from the left
                {
                    player.sprite.setPosition(player.sprite.getPosition() + sf::Vector2(rectTmp.width*-1,.0f));
                    rectP = player.sprite.getGlobalBounds();
                    continue;
                }
                else
                {
                    player.sprite.setPosition(player.sprite.getPosition() + sf::Vector2(rectTmp.width,.0f));
                    rectP = player.sprite.getGlobalBounds();
                    continue;
                }
            }
            
        }
    } 
}

void Scene::updatePhysics(_Float32 dt)
{
    player.updatePhysics(dt);
    level.updatePhysics(dt);

    managePlayerCollisions();
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