#include "player.hpp"

#include <iostream>
#include <algorithm>

#include "resources/resourcesmanager.hpp"
#include "physics/icollidable.hpp"
#include "graphics/statesprite.hpp"
#include "game.hpp"

Player::Player() : sprite()
{
    life=_PLAYER_MAXLIFE;
    maxLife=_PLAYER_MAXLIFE;
}

void Player::setPosition(float x, float y)
{
    sprite->setPosition(x,y);
}

void Player::setY(float y)
{
    sprite->setPosition(sprite->getPosition().x, y);
}

void Player::setX(float x)
{
    sprite->setPosition(x, sprite->getPosition().y);    
}

void Player::initPlayer()
{
    sprite = new graphics::AnimatedStateSprite(resources::ResourcesManager::instance().stateAnimations.getAsset("player"));
    state = State::iddleR;
    sprite->setState(resources::ResourcesManager::PlayerState::iddleR);
    sprite->resetAnim();

    /** scaling **/
    sf::FloatRect rest =sprite->getGlobalBounds();
    sprite->setScale(_PLAYER_WIDTH/rest.width, _PLAYER_HEIGHT/rest.height);
    
    lastPosition = getPosition();
    
    //acceleration.y = -0.1f;
}

void Player::stopJumping()
{
    acceleration.y = -.1f;
    apexJumpTime = 0;
}

void Player::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(*sprite, states);
}


const sf::Vector2f& Player::getPosition() const
{
    return sprite->getPosition();
}

sf::FloatRect Player::getGlobalBounds() const
{
    return sprite->getGlobalBounds();
}

void Player::verticalCollisionEnter(const physics::ICollidable& col)
{
    physics::RigidBody::verticalCollisionEnter(col);
    if(col.getPosition().y >= getPosition().y)
        canJump=true; //can jump if the player touch the ground
}

void Player::updatePhysics(_Float32 dt)
{
    physics::RigidBody::updatePhysics(dt);
    acceleration.y += -9*dt; //gravity
    if (acceleration.y != 0)
    {
        if (acceleration.y > 0)
            apexJumpTime += dt;

        //acceleration.y = std::clamp(acceleration.y*dt, -(float)_TILE_HEIGHT, (float)_TILE_HEIGHT)/dt; //todo veloticity maximum par rapport à dt

        if (apexJumpTime > 0.5 /*apex*/)
        {
            acceleration.y = 0.f;
            apexJumpTime = 0;
        }
        acceleration.y -= jumpSpeed * dt * 2; //TODO gravity
    }
    //std::cout << "yAccel = " << yAcceleration << std::endl;
}

void Player::update(_Float32 dt)
{
    lastPosition = getPosition();
    acceleration.x = 0;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
    {
        sprite->setState(resources::ResourcesManager::PlayerState::runL);
        state = State::left;
        //sprite->setPosition(sprite->getPosition().x - (speed * dt), sprite->getPosition().y);
        acceleration.x = -speed;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        sprite->setState(resources::ResourcesManager::PlayerState::runR);
        state = State::right;
        //sprite->setPosition(sprite->getPosition().x + (speed * dt), sprite->getPosition().y);
        acceleration.x = speed;
    }
    else
    {   
        if(state==State::right){ sprite->setState(resources::ResourcesManager::PlayerState::iddleR);}
        else if(state==State::left){ sprite->setState(resources::ResourcesManager::PlayerState::iddleL);}
        if(state!=State::iddleR)
        {
            state=State::iddleR; //doesn't care about R or L
            sprite->resetAnim();
        }
    }
    
    
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && canJump)
    {
        apexJumpTime = 0;
        acceleration.y = jumpSpeed;
        canJump = false;
    }

    sprite->update(dt);

    //std::cout << "Life : " << life << std::endl;
}