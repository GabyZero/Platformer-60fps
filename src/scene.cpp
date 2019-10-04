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
    sf::FloatRect rectP;
    sf::FloatRect rectTmp;

    for(const physics::ICollidable *col : level.collidable) //todo: don't test * //
    {
        rectP = player.sprite.getGlobalBounds();
        if(!isCollisionTestRelevent(rectP, col->getGlobalBounds())) continue;

        //
        // TODO: moyenne des rect
        //

        //std::cout << sp.getGlobalBounds().height << " " << sp.getGlobalBounds().width << std::endl;
        if(rectP.intersects(col->getGlobalBounds(),rectTmp))
        {
            //std::cout << rectTmp.left << " " << rectTmp.top << " " <<
            //rectTmp.height << " " << rectTmp.width << std::endl;

            /*rectAvg.height += rectTmp.height;
            rectAvg.width  += rectTmp.width;

            rectAvg.left   += rectTmp.left;

            cptRect ++;*/
            player.collisionEnter(*col, rectTmp);
            
        }
    } //foreach collidable

    /*if(cptRect > 0)
    {
        if(rectAvg.height == 0 || rectAvg.height > rectAvg.width)
        {
            std::cout << rectAvg.left / cptRect  << std::endl;
            std::cout << "p:" << rectP.left << std::endl; 
            //left or right
            if(std::abs((rectAvg.left / cptRect) - rectP.left) < 0.001 )
            {
                std::cout << "non" << std::endl;
                player.sprite.setPosition(player.sprite.getPosition() + sf::Vector2((rectAvg.width/cptRect),.0f));               
            }
        }
        else if()
        {
            //top or down;
            if(player.yAcceleration < .0f)//falling ?
            {
                player.sprite.setPosition(player.sprite.getPosition() + sf::Vector2(.0f,(rectAvg.height/cptRect)*-1));
                player.yAcceleration = .0f;
                player.canJump = true;
            }
        }
    }//if cptRect>0 */
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