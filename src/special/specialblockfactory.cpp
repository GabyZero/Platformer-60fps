#include "special/specialblockfactory.hpp"
#include "resources/resourcesmanager.hpp"

namespace special
{

struct flame : public special::IComportment
{
   //using special::IComportment::IComportment;
    public:
        Event event;
        flame(Game &game):IComportment(game){event.type = Event::EventType::PLAYER_DAMAGE;event.playerDamage.damage = 10;} //not okay at all since it's ten per frame todo: need a timer or an invul phase
        virtual void operator()(const physics::ICollidable &, sf::FloatRect )
        {
            game.addEvent(event);
        }
};

struct end : public special::IComportment
{
    public:
        Event event;
        end(Game &game):IComportment(game){event.type = Event::EventType::LEVEL_END;} 
        virtual void operator()(const physics::ICollidable &, sf::FloatRect )
        {
            game.addEvent(event);
        }
};

SpecialBlock<AnimatedBlock>* SpecialBlockFactory::getFlame(Game &game)
{
    return new special::SpecialBlock<AnimatedBlock>(resources::ResourcesManager::instance().animations.getAsset("fire"), new flame(game));
}

SpecialBlock<Block> *SpecialBlockFactory::getEnd(Game& game)
{
    auto pair = resources::ResourcesManager::instance().mapTileSet.getAsset(31); //invisible block
    return new special::SpecialBlock<Block>(pair.first, resources::ResourcesManager::instance().textures.getAsset(pair.second), new end(game));
}

} // namespace special