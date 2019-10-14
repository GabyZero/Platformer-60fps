#ifndef SPECIALBLOCK_HPP
#define SPECIALBLOCK_HPP

#include "physics/icollidable.hpp"
#include "special/icomportment.hpp"

namespace special{

/** Collidable block with special comportment **/
class SpecialBlock : public physics::ICollidable{
    private:
        IComportment& comportment;
        sf::Sprite sprite;
    
    public:
        SpecialBlock(sf::Sprite,IComportment&);

        /** ICollidable implementation **/
        virtual void collisionEnter(const ICollidable &collidable, sf::FloatRect collision) = 0;
        virtual const sf::Vector2f& getPosition() const  = 0 ;
        virtual sf::FloatRect getGlobalBounds() const = 0 ;
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const = 0;
        /** end ICollidable **/
};
}

#endif