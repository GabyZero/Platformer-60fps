#include "physics/collisiondetector.hpp"

#include "debug/debugger.hpp"

#include "game.hpp"

#include <iostream>

namespace physics
{
    bool CollisionDetector::isBetween(float n, float a, float b)
    {
        return (n - a) * (n - b) <= 0 ;  
    }

    bool CollisionDetector::lineLineIntersect(const Line& line1, const Line& line2, sf::FloatRect& collision)
    {
        //std::cout << "Testing: [";Debugger::print(line1.p1);Debugger::print(line1.p2);std::cout<<"] versus ";
                 //std::cout << "[";Debugger::print(line2.p1),Debugger::print(line2.p2);std::cout<<"]=>";
  
        float dem = ((line2.p2.y-line2.p1.y)*(line1.p2.x-line1.p1.x)) - ((line2.p2.x-line2.p1.x)*(line1.p2.y-line1.p1.y));
        if(dem==0) {/*std::cout << std::endl;*/return false;} //line are parralel (if numerator==0 then they are coincident)

        float uA = (((line2.p2.x-line2.p1.x)*(line1.p1.y-line2.p1.y)) - ((line2.p2.y-line2.p1.y)*(line1.p1.x-line2.p1.x)))/dem;
        
        float uB = (((line1.p2.x-line1.p1.x)*(line1.p1.y-line2.p1.y)) - ((line1.p2.y-line1.p1.y)*(line1.p1.x-line2.p1.x)))/dem;

        //std::cout << uA << " " << uB << std::endl;

        //if uA or uB > 1 then the intersection is not on the line
        //if uA and uB == 0 then the lines are parallel

        if(uA>=0 && uA <=1 && uB>=0 && uB<=1)
        {
            collision = sf::FloatRect(line1.p1.x+(uA*(line1.p2.x-line1.p1.x)),
                                      line1.p1.y+(uA*(line1.p2.y-line1.p1.y)),1,1);
            return true;
        }
        else return false;
    }

    float distance2(const sf::Vector2f& p1, const sf::Vector2f& p2)
    {
        return (p1.x-p2.x)*(p1.x-p2.x) + (p1.y-p2.y)*(p1.y-p2.y);
    }

    bool CollisionDetector::lineRectIntersect(const Line& line, const sf::FloatRect& rect, sf::FloatRect& collision)
    {
        sf::FloatRect* res = nullptr;
        float dres = 0;
        sf::FloatRect left, right, top, bottom; //width and height = 0 means no collision

        //std::cout << "*** LineRect ***" << std::endl;
        //std::cout << "[";Debugger::print(line.p1);Debugger::print(line.p2);std::cout << "] versus "; Debugger::print(rect); std::cout << std::endl;
        
        //we have to test every side since it can have more than one collision
        if(lineLineIntersect(line, {rect.left, rect.top, rect.left, rect.top+rect.height},left))
        {
            res = &left;
            dres = distance2(line.p1,sf::Vector2f(left.left,left.top));
        }
        if(lineLineIntersect(line, {rect.left+rect.width, rect.top, rect.left+rect.width, rect.top+rect.height},right))
        {
            if(res==nullptr) res =&right;
            float dright = distance2(line.p1,sf::Vector2f(right.left,right.top));
            if(dright<dres)
            {
                dres = dright; res = &right;
            }
        }
        if(lineLineIntersect(line, {rect.left, rect.top, rect.left+rect.width, rect.top},top))
        {   
            if(res==nullptr) res =&top;
            float dtop = distance2(line.p1,sf::Vector2f(top.left,top.top));
            if(dtop<dres)
            {
                dres = dtop; res = &top;
            }           
        }
        if(lineLineIntersect(line, {rect.left, rect.top+rect.height, rect.left+rect.width, rect.top+rect.height},bottom))
        {
            if(res==nullptr) res =&bottom;
            float dbottom = distance2(line.p1,sf::Vector2f(bottom.left,bottom.top));
            if(dbottom<dres)
            {
                dres = dbottom; res = &bottom;
            }            
        }
        if(res!=nullptr)
        {
            collision = *res;
            //std::cout << "Line intersect found the next collision" << std::endl;
            //Game::setPause(true);
            return true;
        }
        else return false;
    }

    bool CollisionDetector::nextFrameCollision(RigidBody& rb, const ICollidable &col, float dt, sf::FloatRect& collision)
    {
        sf::FloatRect nextpos = rb.nextPosition();
        //std::cout << "TEST COLLISION" << std::endl;
        //Debugger::print(nextpos); std::cout << " - "; Debugger::print(col.getGlobalBounds()); std::cout << std::endl;
        Line ray;
        ray.p1.x = rb.getGlobalBounds().left; ray.p1.y = rb.getGlobalBounds().top;
        ray.p2.x = nextpos.left; ray.p2.y = nextpos.top;

        if(lineRectIntersect(ray, col.getGlobalBounds(), collision))
        {
            collision.height = std::abs(collision.top - nextpos.top) 
                            + (((rb.acceleration.y>0&&nextpos.top<col.getGlobalBounds().top) ||rb.acceleration.y<0)?nextpos.height:0);
            collision.width =  std::abs(collision.left - nextpos.left)
                            + (((rb.getGlobalBounds().left>col.getGlobalBounds().left&&nextpos.left<col.getGlobalBounds().left) ||rb.getGlobalBounds().left<col.getGlobalBounds().left)?nextpos.width:0);
            return true;
        }
        else return nextpos.intersects(col.getGlobalBounds(),collision)  ;

    }

    /*bool CollisionDetector::nextFrameVerticalCollision(const RigidBody& rb, const ICollidable &col, float dt)
    {
        sf::Vector2f rbpos = rb.lastposition;
        sf::FloatRect rbgb = rb.getGlobalBounds();
        
        // need the third ray in the center, if my rb width > coll width
        Line ray1, ray2, ray3;
        Line line;
        
        if(rb.acceleration.y<0)
        {         
            ray1.p1 = rbpos; ray1.p1.y+=rbgb.height;
            ray2.p1 = rbpos; ray2.p1.y+=rbgb.height; ray2.p1.x+=rbgb.width;
            ray3.p1 = rbpos; ray3.p1.y+=rbgb.height; ray3.p1.x+=(rbgb.width/2.0f);
            line.p1 = col.getPosition();    
        }
        else if(rb.acceleration.y>0)
        {
            ray1.p1 = rbpos;
            ray2.p1 = rbpos; ray2.p1.x+=rbgb.width;
            ray3.p1 = rbpos; ray3.p1.x+=(rbgb.width/2.0f);
            line.p1 = col.getPosition(); line.p1.y += col.getGlobalBounds().height;
        }
        
        line.p2 = line.p1; 
        line.p2.x += col.getGlobalBounds().width;

        ray1.p2 = ray1.p1; ray1.p2.y -= (rb.acceleration.y*dt);
        ray2.p2 = ray2.p1; ray2.p2.y -= (rb.acceleration.y*dt);
        ray3.p2 = ray3.p1; ray3.p2.y -= (rb.acceleration.y*dt);

        return (isBetween(ray1.p1.x, line.p1.x, line.p2.x) && isBetween(line.p1.y, ray1.p1.y, ray1.p2.y)) ||
               (isBetween(ray2.p1.x, line.p1.x, line.p2.x) && isBetween(line.p1.y, ray2.p1.y, ray2.p2.y)) ||
               (isBetween(ray3.p1.x, line.p1.x, line.p2.x) && isBetween(line.p1.y, ray3.p1.y, ray3.p2.y)) ; 

    }

    bool CollisionDetector::nextFrameHorizontalCollision(const RigidBody& rb, const ICollidable &col, float dt)
    {
        if(rb.acceleration.x==0) return false;
        sf::Vector2f rbpos = rb.lastposition;
        sf::FloatRect rbgb = rb.getGlobalBounds();
        // need the third ray in the center, if my rb height > coll height
        Line ray1, ray2, ray3;
        Line line;

        if(rb.acceleration.x<0)
        {
            ray1.p1 = rbpos;
            ray2.p1 = rbpos; ray2.p1.y+=rbgb.height;
            ray3.p1 = rbpos; ray3.p1.y+=(rbgb.height/2.0f);
            line.p1 = col.getPosition(); line.p1.x+=col.getGlobalBounds().width;
        }
        else if(rb.acceleration.x>0)
        {
            ray1.p1 = rbpos; ray1.p1.x+=rbgb.width;
            ray2.p1 = rbpos; ray2.p1.x+=rbgb.width; ray2.p1.y += rbgb.height;
            ray3.p1 = rbpos; ray3.p1.x+=rbgb.width; ray3.p1.y+=(rbgb.height/2.0f);
            line.p1 = col.getPosition();
        }

        line.p2 = line.p1; 
        line.p2.y += col.getGlobalBounds().height;

        ray1.p2 = ray1.p1; ray1.p2.x += (rb.acceleration.x*dt);
        ray2.p2 = ray2.p1; ray2.p2.x += (rb.acceleration.x*dt);
        ray3.p2 = ray3.p1; ray3.p2.x += (rb.acceleration.x*dt);

        return (isBetween(ray1.p1.y, line.p1.y, line.p2.y) && isBetween(line.p1.x, ray1.p1.x, ray1.p2.x)) ||
               (isBetween(ray2.p1.y, line.p1.y, line.p2.y) && isBetween(line.p1.x, ray2.p1.x, ray2.p2.x)) ||
               (isBetween(ray3.p1.y, line.p1.y, line.p2.y) && isBetween(line.p1.x, ray3.p1.x, ray3.p2.x)) ; 

    }*/
}