#include "scene.hpp"

#include "resources/resourcesmanager.hpp"
#include <iostream>

#include "animatedblock.hpp"
#include "resources/resourcesmanager.hpp"
#include "special/specialblock.hpp"
#include "special/icomportment.hpp"

class duchmol : public special::IComportment
{
    virtual void operator()(const physics::ICollidable &collidable, sf::FloatRect collision)
    {
        std::cout << "wesh alors " << std::endl;
    }

};

Scene::Scene(Game &_game):
game(_game),
level(game)
{
}

void Scene::initScene()
{
    player.initPlayer();
    level.initLevel();
    //std::cout << "test : " << player.sprite.getPosition().x << " " << player.sprite.getPosition().x << std::endl;
    special::SpecialBlock<AnimatedBlock> *test = new special::SpecialBlock<AnimatedBlock>(resources::ResourcesManager::instance().animations.getAsset("fire"), *new duchmol());
    test->setPosition(player.getPosition().x + 20 , player.getPosition().y);
    level.trigerrable.push_back(test);
}

/** return true if the collision test is relevent **/
bool isCollisionTestRelevent(const sf::FloatRect &player, const sf::FloatRect &collidable)
{
    return std::abs(player.top - collidable.top) < 16 
        && std::abs(player.left - collidable.left) <16;
}

void Scene::managePlayerCollisions()
{
    sf::FloatRect rectP;
    sf::FloatRect rectTmp;

    for(physics::ICollidable *col : level.collidable) //todo: don't test * //
    {
        rectP = player.sprite.getGlobalBounds();
        if(!isCollisionTestRelevent(rectP, col->getGlobalBounds())) continue;

        //std::cout << sp.getGlobalBounds().height << " " << sp.getGlobalBounds().width << std::endl;
        if(rectP.intersects(col->getGlobalBounds(),rectTmp))
        {
            std::cout << col->getGlobalBounds().left << " " << col->getGlobalBounds().top << std::endl;
            std::cout << rectTmp.left << " " << rectTmp.top << " " <<
            rectTmp.height << " " << rectTmp.width << std::endl;

            player.collisionEnter(*col, rectTmp);
            col->collisionEnter(player, rectTmp);        
        }
    } //foreach collidable

    for(physics::ICollidable *col : level.trigerrable) //todo: don't test * //
    {
        rectP = player.sprite.getGlobalBounds();
        if(!isCollisionTestRelevent(rectP, col->getGlobalBounds())) continue;

        //std::cout << sp.getGlobalBounds().height << " " << sp.getGlobalBounds().width << std::endl;
        if(rectP.intersects(col->getGlobalBounds(),rectTmp))
        {
            //player.collisionEnter(*col, rectTmp); player dont know since it's a trigger
            col->collisionEnter(player, rectTmp);        
        }
    } //foreach collidable
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