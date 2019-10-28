#include "physics/rigidbody.hpp"

namespace physics
{
    void RigidBody::horizontalCollisionEnter(const ICollidable &collidable)
    {
        sf::Vector2f cpos = collidable.getPosition();
        float cwidth = collidable.getGlobalBounds().width;
        if(cpos.x>getPosition().x)
        {
            setX(cpos.x-getGlobalBounds().width);
        }
        else
        {
            setX(cpos.x+cwidth);
        }
        acceleration.x = 0;
    }

    void RigidBody::verticalCollisionEnter(const ICollidable &collidable)
    {
        sf::Vector2f cpos = collidable.getPosition();
        float cheight = collidable.getGlobalBounds().height;
        if(cpos.y>getPosition().y)
        {
            setY(cpos.y-getGlobalBounds().height);
        }
        else
        {
            setY(cpos.y+cheight);
        }
        acceleration.y = 0;
    }

    void RigidBody::updatePhysics(float dt)
    {
        sf::Vector2f pos = getPosition();
        setPosition(
            pos.x + (acceleration.x*dt),
            pos.y + (acceleration.y*dt)
        );
    }
}