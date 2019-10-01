#include "player.hpp"
#include <iostream>

#include "resources/resourcesmanager.hpp"

Player::Player():
sprite()
{
}

void Player::initPlayer()
{
    sprite.setTexture(resources::ResourcesManager::instance().textures.getAsset("player"));
    sprite.setPosition(32,100);
    state = State::iddle;
}

void Player::stopJumping()
{
    yAcceleration =-.1f;
    apexJumpTime = 0;
}

void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(sprite, states);
}

void Player::updatePhysics(_Float32 dt)
{
    yAcceleration +=-.1f; //gravity
    if(yAcceleration != 0)
    {
        if(yAcceleration > 0) apexJumpTime+=dt;

        sprite.setPosition(sprite.getPosition().x, sprite.getPosition().y - (yAcceleration*dt));

        if(apexJumpTime>0.5/*apex*/) 
        {
            yAcceleration = 0.f;
            apexJumpTime = 0;
        }
        yAcceleration-=jumpSpeed*dt*2; //TODO gravity
    }
}

void Player::update(_Float32 dt)
{
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
    {
        sprite.setPosition(sprite.getPosition().x-(speed*dt), sprite.getPosition().y);
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        sprite.setPosition(sprite.getPosition().x+(speed*dt), sprite.getPosition().y);
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && canJump)
    {
        yAcceleration += jumpSpeed;
        canJump = false;
    }
}