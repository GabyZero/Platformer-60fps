#ifndef RIGIDBODY_HPP
#define RIGIDBODY_HPP

#include "physics/icollidable.hpp"

namespace physics{

/** manage collision, acceleration and movement
 *  doen't manage gravity **/
class RigidBody : public ICollidable{
    public:
        sf::Vector2f acceleration;
        sf::Vector2f nextposition;
        
        /** icollidable **/
        /*virtual void verticalCollisionEnter(const ICollidable &collidable);
        virtual void horizontalCollisionEnter(const ICollidable &collidable);*/
        virtual void collisionEnter(const ICollidable &collidable, sf::FloatRect collision);
        virtual const sf::Vector2f& getPosition() const  = 0 ;
        virtual sf::FloatRect getGlobalBounds() const = 0 ;
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const = 0;
        virtual void update(float);
        
        /** rigid body **/
        virtual void updatePhysics(float);

        sf::FloatRect nextPosition();

    protected:
        /**rigidbody **/
        virtual void setPosition(sf::Vector2f) = 0;
        virtual void setPosition(float,float) = 0;
        virtual void setX(float) = 0;
        virtual void setY(float) = 0;
};

}
#endif
