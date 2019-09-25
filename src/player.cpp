#include "player.hpp"
#include <iostream>
Player::Player():
texture(),sprite()
{
    texture.loadFromFile("player.png");
    sprite.setTexture(texture);
    sprite.setPosition(32,250);
    state = State::iddle;
}

void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(sprite, states);
}

void Player::UpdatePhysics(_Float32 dt)
{
    if(yAcceleration != 0)
    {
        static _Float32 time = 0;
        if(yAcceleration > 0) time+=dt;

        sprite.setPosition(sprite.getPosition().x, sprite.getPosition().y - (yAcceleration*dt));

        if(time>0.8/*apex*/) 
        {
            yAcceleration = 0.f;
            time = 0;
        }
        yAcceleration-=jumpSpeed*dt; //TODO gravity
    }
}

void Player::Update(_Float32 dt)
{
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
    {
        sprite.setPosition(sprite.getPosition().x-(speed*dt), sprite.getPosition().y);
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        sprite.setPosition(sprite.getPosition().x+(speed*dt), sprite.getPosition().y);
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && yAcceleration == 0)
    {
        yAcceleration += jumpSpeed;
    }
}