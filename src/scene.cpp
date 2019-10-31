#include "scene.hpp"

#include "debug/debugger.hpp"

#include "resources/resourcesmanager.hpp"
#include <iostream>

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
bool isCollisionTestRelevent(const sf::FloatRect &player, const sf::FloatRect &collidable, sf::Vector2f accel)
{
    return std::abs(player.top - collidable.top) <= (_PLAYER_HEIGHT+std::abs(accel.y))
        && std::abs(player.left - collidable.left)<= (_PLAYER_WIDTH+std::abs(accel.x)); 
}

void Scene::managePlayerCollisions(float dt)
{
    std::cout << "**** COLLISIONS ****" << std::endl;
    sf::FloatRect rectP;
    sf::FloatRect rectTmp;
    for(physics::ICollidable *col : level.collidable) 
    {
        rectP = player.getGlobalBounds();
        if(!isCollisionTestRelevent(rectP, col->getGlobalBounds(), player.acceleration*dt)) continue;

        //std::cout << sp.getGlobalBounds().height << " " << sp.getGlobalBounds().width << std::endl;
        /*if(physics::CollisionDetector::nextFrameVerticalCollision(player,*col, dt))
        {
            player.verticalCollisionEnter(*col);
            col->verticalCollisionEnter(player);
        }
        if(physics::CollisionDetector::nextFrameHorizontalCollision(player, *col, dt))
        {
            player.horizontalCollisionEnter(*col);
            col->horizontalCollisionEnter(player);   
        }*/
        if(physics::CollisionDetector::nextFrameCollision(player, *col, dt,rectTmp))
        {
            //std::cout << rectTmp << std::endl;
            player.collisionEnter(*col, rectTmp);
            col->collisionEnter(*col, rectTmp);
        }
    } //foreach collidable


    for(physics::ICollidable *col : level.trigerrable)
    {
        rectP = player.sprite->getGlobalBounds();
        if(!isCollisionTestRelevent(rectP, col->getGlobalBounds(),player.acceleration*dt)) continue;

        //std::cout << sp.getGlobalBounds().height << " " << sp.getGlobalBounds().width << std::endl;
        if(rectP.intersects(col->getGlobalBounds(),rectTmp))
        {
            //player.collisionEnter(*col, rectTmp); player dont know since it's a trigger
            //col->collisionEnter(player, rectTmp);        
        }
    } //foreach triggerable
    std::cout << "**** FIN COLLISIONS ****" << std::endl;
}

void Scene::updatePhysics(_Float32 dt)
{   
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