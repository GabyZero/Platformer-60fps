#include "physics/rigidbody.hpp"

#include <iostream>

namespace physics
{
    void RigidBody::horizontalCollisionEnter(const ICollidable &collidable)
    {
        sf::Vector2f cpos = collidable.getPosition();
        float cwidth = collidable.getGlobalBounds().width;
        if(cpos.x>lastposition.x)
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
        std::cout << "non" << std::endl;
        sf::Vector2f cpos = collidable.getPosition();
        float cheight = collidable.getGlobalBounds().height;
        if(cpos.y>lastposition.y)
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
        lastposition = getPosition();
        setPosition(
            lastposition.x + (acceleration.x*dt),
            lastposition.y - (acceleration.y*dt)
        );
    }
}