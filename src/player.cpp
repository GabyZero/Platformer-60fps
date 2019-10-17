#include "player.hpp"

#include <iostream>
#include <algorithm>

#include "resources/resourcesmanager.hpp"
#include "physics/icollidable.hpp"
#include "game.hpp"

Player::Player() : sprite()
{
    life=_PLAYER_MAXLIFE;
    maxLife=_PLAYER_MAXLIFE;
}

void Player::initPlayer()
{
    sprite.setTexture(resources::ResourcesManager::instance().textures.getAsset("player"));
    sprite.setPosition(32, 100);
    state = State::iddle;
}

void Player::stopJumping()
{
    yAcceleration = -.1f;
    apexJumpTime = 0;
}

void Player::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(sprite, states);
}

/** ICollidable implementation **/
void Player::collisionEnter(const physics::ICollidable &collidable, sf::FloatRect collision)
{
    if (collision.width > collision.height)
    {
        //top or down
        if (collision.top == collidable.getPosition().y && yAcceleration < .0f) //is the player falling ?
        {
            sprite.setPosition(sprite.getPosition() + sf::Vector2(.0f, collision.height * -1));
            yAcceleration = .0f;
            canJump = true;
        }
        else if (yAcceleration > .0f) //is the player jumping ?
        {
            sprite.setPosition(sprite.getPosition() + sf::Vector2(.0f, collision.height));
            stopJumping();
        }
    }
    else
    {
        //left or right
        if (collision.left == collidable.getPosition().x) //from the left
        {
            sprite.setPosition(sprite.getPosition() + sf::Vector2(collision.width * -1, .0f));
        }
        else
        {
            sprite.setPosition(sprite.getPosition() + sf::Vector2(collision.width, .0f));
        }
    }
    
}

const sf::Vector2f& Player::getPosition() const
{
    return sprite.getPosition();
}

sf::FloatRect Player::getGlobalBounds() const
{
    return sprite.getGlobalBounds();
}

/** en icollidable **/

void Player::updatePhysics(_Float32 dt)
{
    yAcceleration += -9*dt; //gravity
    if (yAcceleration != 0)
    {
        if (yAcceleration > 0)
            apexJumpTime += dt;

        //yAcceleration = std::clamp(yAcceleration*dt, -16.0f, 16.0f)/dt; todo veloticity maximum par rapport à dt

        sprite.setPosition(sprite.getPosition().x, sprite.getPosition().y - (yAcceleration * dt));

        if (apexJumpTime > 0.5 /*apex*/)
        {
            yAcceleration = 0.f;
            apexJumpTime = 0;
        }
        yAcceleration -= jumpSpeed * dt * 2; //TODO gravity
    }
    //std::cout << "yAccel = " << yAcceleration << std::endl;
}

void Player::update(_Float32 dt)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
    {
        sprite.setPosition(sprite.getPosition().x - (speed * dt), sprite.getPosition().y);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        sprite.setPosition(sprite.getPosition().x + (speed * dt), sprite.getPosition().y);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && canJump)
    {
        yAcceleration = jumpSpeed;
        canJump = false;
    }

    std::cout << "Life : " << life << std::endl;
}