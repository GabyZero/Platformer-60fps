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

void Player::initPlayer()
{
    //sprite.setTexture(resources::ResourcesManager::instance().textures.getAsset("player"));
    //sprite.setPosition(32, 100);
    sprite = new graphics::AnimatedStateSprite(resources::ResourcesManager::instance().stateAnimations.getAsset("player"));
    lastPosition = getPosition();
    state = State::iddle;
    sf::FloatRect rest =sprite->getGlobalBounds();
    sprite->setScale(_PLAYER_WIDTH/rest.width, _PLAYER_HEIGHT/rest.height);
    std::cout << rest.width << "  " << rest.height << std::endl;
}

void Player::stopJumping()
{
    yAcceleration = -.1f;
    apexJumpTime = 0;
}

void Player::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(*sprite, states);
}

/** ICollidable implementation **/
void Player::collisionEnter(const physics::ICollidable &collidable, sf::FloatRect collision)
{   
    if (collision.width > collision.height)
    {
        //top or down
        if (collision.top == collidable.getGlobalBounds().top && yAcceleration < .0f) //is the player falling ?
        {
            sprite->setPosition(sprite->getPosition() + sf::Vector2(.0f, collision.height * -1));
            yAcceleration = .0f;
            canJump = true;
        }
        else if (yAcceleration > .0f) //is the player jumping ?
        {
            if(std::abs(lastPosition.x-collidable.getPosition().x)>=15.9) return;
            std::cout << "(" << getGlobalBounds().left << "," << getGlobalBounds().top << ")";
            std::cout << " with (" << collidable.getGlobalBounds().left << "," << collidable.getGlobalBounds().top <<")->";
            std::cout << "[" << collision.width << "x" << collision.height << "]" << std::endl;
            sprite->setPosition(sprite->getPosition() + sf::Vector2(.0f, collision.height));
            stopJumping();
        }
    }
    else
    {
        //left or right
        if (collision.left == collidable.getPosition().x) //from the left
        {
            sprite->setPosition(sprite->getPosition() + sf::Vector2(collision.width * -1, .0f));
        }
        else
        {
            sprite->setPosition(sprite->getPosition() + sf::Vector2(collision.width, .0f));
        }
    }
    
}

const sf::Vector2f& Player::getPosition() const
{
    return sprite->getPosition();
}

sf::FloatRect Player::getGlobalBounds() const
{
    return sprite->getGlobalBounds();
}

/** en icollidable **/

void Player::updatePhysics(_Float32 dt)
{
    yAcceleration += -9*dt; //gravity
    if (yAcceleration != 0)
    {
        if (yAcceleration > 0)
            apexJumpTime += dt;

        yAcceleration = std::clamp(yAcceleration*dt, -(float)_TILE_HEIGHT, (float)_TILE_HEIGHT)/dt; //todo veloticity maximum par rapport à dt
        sprite->setPosition(sprite->getPosition().x, sprite->getPosition().y - (yAcceleration * dt));

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
    lastPosition = getPosition();
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
    {
        sprite->setPosition(sprite->getPosition().x - (speed * dt), sprite->getPosition().y);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        sprite->setPosition(sprite->getPosition().x + (speed * dt), sprite->getPosition().y);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && canJump)
    {
        apexJumpTime = 0;
        yAcceleration = jumpSpeed;
        canJump = false;
    }

    sprite->update(dt);

    //std::cout << "Life : " << life << std::endl;
}