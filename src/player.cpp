#include "player.hpp"

Player::Player():
texture(),sprite()
{
    texture.loadFromFile("player.png");
    sprite.setTexture(texture);
    sprite.setPosition(32,32);
    state = State::iddle;
}

void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(sprite, states);
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
}