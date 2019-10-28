#ifndef COLLISIONDETECTOR_HPP
#define COLLISIONDETECTOR_HPP

#include "physics/rigidbody.hpp"
#include "physics/icollidable.hpp"

namespace physics{

struct CollisionDetector
{   
    struct Ray
    {
        sf::Vector2f pos;
        sf::Vector2f dir;
    };

    struct Line
    {
        sf::Vector2f p1, p2;
    };

    static bool isBetween(float n, float a, float b)
    {
        return (n - a) * (n - b) <= 0 ;  
    }

    static bool nextFrameVerticalCollision(const RigidBody& rb, const ICollidable &col, float dt)
    {
        sf::Vector2f rbpos = rb.getPosition();
        sf::FloatRect rbgb = rb.getGlobalBounds();
        
        Line ray1, ray2;
        Line line;
        
        if(rb.acceleration.y>0)
        {         
            ray1.p1 = rbpos; ray1.p1.y+=rbgb.height;
            ray2.p1 = rbpos; ray2.p1.y+=rbgb.height; ray2.p1.x+=rbgb.width;
            line.p1 = col.getPosition();    
        }
        else if(rb.acceleration.y<0)
        {
            ray1.p1 = rbpos;
            ray2.p1 = rbpos; ray2.p1.x+=rbgb.width;
            line.p1 = col.getPosition(); line.p1.y += col.getGlobalBounds().height;
        }
        
        line.p2 = line.p1; 
        line.p2.x += col.getGlobalBounds().width;

        ray1.p2 = ray1.p1; ray1.p2.y += (rb.acceleration.y*dt);
        ray2.p2 = ray2.p1; ray2.p2.y += (rb.acceleration.y*dt);

        return (isBetween(ray1.p1.x, line.p1.x, line.p2.x) && isBetween(line.p1.y, ray1.p1.y, ray1.p2.y)) ||
               (isBetween(ray2.p1.x, line.p1.x, line.p2.x) && isBetween(line.p1.y, ray2.p1.y, ray2.p2.y)) ;
    }

    static bool nextFrameHorizontalCollision(const RigidBody& rb, const ICollidable &col, float dt)
    {
        if(rb.acceleration.x>0)
        {

        }
        else if(rb.acceleration.x<0)
        {
            
        }
    }
};

}

#endif