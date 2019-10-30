#ifndef COLLISIONDETECTOR_HPP
#define COLLISIONDETECTOR_HPP

#include "physics/rigidbody.hpp"
#include "physics/icollidable.hpp"

namespace physics{

struct CollisionDetector
{   
    struct Line
    {
        sf::Vector2f p1, p2;

        Line(){}
        Line(float x1, float y1, float x2, float y2):p1(x1,y1),p2(x2,y2){}
    };

    static bool isBetween(float n, float a, float b);
    static bool lineLineIntersect(const Line& line1, const Line& line2, sf::FloatRect& collision);
    static bool lineRectIntersect(const Line& line, const sf::FloatRect& rect, sf::FloatRect& collision);
    static bool nextFrameCollision(RigidBody& rb, const ICollidable &col, float dt, sf::FloatRect& collision);
    /*static bool nextFrameVerticalCollision(const RigidBody& rb, const ICollidable &col, float dt);
    static bool nextFrameHorizontalCollision(const RigidBody& rb, const ICollidable &col, float dt);*/


};//class

}//namespace

#endif