#ifndef RIGIDBODY_HPP
#define RIGIDBODY_HPP

#include "physics/icollidable.hpp"

namespace physics{

class RigidBody : public ICollidable{
    private:
        sf::Vector2f acceleration;
    public:

        virtual void collisionEnter(const ICollidable &collidable, sf::FloatRect collision);
        virtual const sf::Vector2f& getPosition() const  = 0 ;
        virtual sf::FloatRect getGlobalBounds() const = 0 ;
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const = 0;
        virtual void update(float)=0;
        virtual void updatePhysics(float);
};

}
#endif
