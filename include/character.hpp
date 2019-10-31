#ifndef CHARACTER_HPP
#define CHARACTER_HPP

#include "physics/rigidbody.hpp"

class Character : public physics::RigidBody{
    private:
        sf::Sprite sprite;
        
    public:
        virtual void verticalCollisionEnter(const ICollidable &collidable);
        virtual void horizontalCollisionEnter(const ICollidable &collidable);
        
        virtual const sf::Vector2f& getPosition() const  = 0 ;
        virtual sf::FloatRect getGlobalBounds() const = 0 ;
        
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const = 0;
        virtual void update(float)=0;
        virtual void updatePhysics(float);
        
        virtual void setPosition(float,float);
        virtual void setX(float);
        virtual void setY(float);
};

#endif