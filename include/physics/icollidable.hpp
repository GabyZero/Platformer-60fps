#ifndef ICOLLIDABLE_HPP
#define ICOLLIDABLE_HPP

#include <SFML/Graphics.hpp>
#include "iobject.hpp"

namespace physics{

/**
 * All collidable must be drawable 
 **/
class ICollidable : public sf::Drawable, public IObject {
    public:
        /*virtual void verticalCollisionEnter(const ICollidable &collidable) = 0;
        virtual void horizontalCollisionEnter(const ICollidable &collidable) = 0;*/
        virtual void collisionEnter(const ICollidable &collidable, sf::FloatRect collision) = 0;
        virtual const sf::Vector2f& getPosition() const  = 0 ;
        virtual sf::FloatRect getGlobalBounds() const = 0 ;
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const = 0;
        virtual void update(float) = 0;
        virtual void updatePhysics(float){}
};

}

#endif