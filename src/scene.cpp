#include "scene.hpp"

#include "resources/resourcesmanager.hpp"
#include <iostream>
#include "debug/debugger.hpp"

#include "animatedblock.hpp"
#include "graphics/statesprite.hpp"
#include "resources/resourcesmanager.hpp"
#include "special/specialblock.hpp"
#include "special/icomportment.hpp"
#include "physics/collisiondetector.hpp"

#include "event.hpp"

class duchmol : public special::IComportment
{
   using special::IComportment::IComportment;
    public:
        Event event;
        duchmol(Game &game):IComportment(game){event.type = Event::EventType::PLAYER_DAMAGE;event.playerDamage.damage = 10;}
        virtual void operator()(const physics::ICollidable &, sf::FloatRect )
        {
            game.addEvent(event);
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
    special::SpecialBlock<AnimatedBlock> *test = new special::SpecialBlock<AnimatedBlock>(resources::ResourcesManager::instance().animations.getAsset("fire"), *new duchmol(game));
    test->setPosition(player.getPosition().x + 20 , player.getPosition().y);
    level.trigerrable.push_back(test);

    std::cout << "Scene loaded" << std::endl;
}

/** return true if the collision test is relevent **/
bool isCollisionTestRelevent(const sf::FloatRect &player, const sf::FloatRect &collidable)
{
    return std::abs(player.top - collidable.top) < 20  
        && std::abs(player.left - collidable.left) <20;
}

void Scene::managePlayerCollisions(float dt)
{
    sf::FloatRect rectP;
    sf::FloatRect rectTmp;

    for(physics::ICollidable *col : level.collidable) 
    {
        rectP = player.sprite->getGlobalBounds();
        if(!isCollisionTestRelevent(rectP, col->getGlobalBounds())) continue;

        //std::cout << sp.getGlobalBounds().height << " " << sp.getGlobalBounds().width << std::endl;
        if(physics::CollisionDetector::nextFrameVerticalCollision(player,*col, dt))
        {
            player.verticalCollisionEnter(*col);
            col->verticalCollisionEnter(player);
        }
    } //foreach collidable


    for(physics::ICollidable *col : level.trigerrable)
    {
        rectP = player.sprite->getGlobalBounds();
        if(!isCollisionTestRelevent(rectP, col->getGlobalBounds())) continue;

        //std::cout << sp.getGlobalBounds().height << " " << sp.getGlobalBounds().width << std::endl;
        if(rectP.intersects(col->getGlobalBounds(),rectTmp))
        {
            //player.collisionEnter(*col, rectTmp); player dont know since it's a trigger
            //col->collisionEnter(player, rectTmp);        
        }
    } //foreach triggerable
}

void Scene::updatePhysics(_Float32 dt)
{   
    /** detect the collision before **/
    managePlayerCollisions(dt);

    player.updatePhysics(dt);
    level.updatePhysics(dt);

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