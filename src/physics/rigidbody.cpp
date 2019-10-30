#include "physics/rigidbody.hpp"

#include "debug/debugger.hpp"
#include "game.hpp"

#include <iostream>

namespace physics
{
sf::FloatRect RigidBody::nextPosition() 
{
    sf::FloatRect res = getGlobalBounds();

    res.top = nextposition.y;
    res.left = nextposition.x;

    return res;
}

/*void RigidBody::horizontalCollisionEnter(const ICollidable &collidable)
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
    }*/

void RigidBody::collisionEnter(const ICollidable &collidable, sf::FloatRect collision)
{   
    std::cout << "col : "; Debugger::print(collision); std::cout << std::endl;
    sf::Vector2f nPos = nextposition;
    sf::Vector2f lPos = getPosition();
    if (std::abs(lPos.x - collidable.getPosition().x) < std::abs(lPos.y - collidable.getPosition().y))
    {
        //top or down
        if (collision.top == collidable.getGlobalBounds().top && acceleration.y < .0f) //is the body falling ?
        {
            nextposition = (nPos + sf::Vector2(.0f, collision.height * -1));
            acceleration.y = -.1f;
            //canJump = true;
        }
        else if (acceleration.y > .0f) //is the player jumping ?
        {
            if (std::abs(lPos.x - collidable.getPosition().x) >= 15.9)
                return;
            std::cout << "OUCH MY HEAD collision:";
            Debugger::print(collision); std::cout << " on "; Debugger::print(collidable.getGlobalBounds());
            //Game::setPause(true);
            nextposition = (nPos + sf::Vector2(.0f, collision.height));
            acceleration.y = -.1f;
        }
    }
    else
    {   
        if(acceleration.x==0)
        {
            std::cout << "Shall not be there" << std::endl;
            Game::setPause(true);
            return;
        }
        //left or right
        if (collision.left == collidable.getPosition().x) //from the left
        {
            nextposition = (nPos + sf::Vector2(collision.width * -1, .0f));
            acceleration.x = 0;
        }
        else 
        {
            nextposition = (nPos + sf::Vector2(collision.width, .0f));
            acceleration.x = 0;
        }
    }
    //Game::setPause(true);
}

void RigidBody::update(float dt )
{   
    std::cout << "Last position : ";  Debugger::print(getPosition());
    std::cout << " Accelration : ";   Debugger::print(acceleration);
    sf::Vector2f pos = getPosition();
    nextposition.x = pos.x + acceleration.x*dt;
    nextposition.y = pos.y - acceleration.y*dt;
    std::cout << " Next position : "; Debugger::print(nextposition); std::cout << std::endl;
}

void RigidBody::updatePhysics(float dt)
{
    setPosition(nextposition);
}
} // namespace physics