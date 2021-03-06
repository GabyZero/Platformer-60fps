#include "player.hpp"

#include <iostream>
#include <algorithm>

#include "resources/resourcesmanager.hpp"
#include "physics/icollidable.hpp"
#include "graphics/statesprite.hpp"
#include "game.hpp"

#include "debug/debugger.hpp"

Player::Player(Game &_game) : sprite(), game(_game)
{
    life=_PLAYER_MAXLIFE;
    maxLife=_PLAYER_MAXLIFE;
}

void Player::setPosition(float x, float y)
{
    sprite->setPosition(x,y);
}

void Player::setPosition(sf::Vector2f pos)
{
    sprite->setPosition(pos);
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
    
    jumpSound.setBuffer(resources::ResourcesManager::instance().sounds.getAsset("jump1"));
    jumpSound.setRelativeToListener(true);
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

/*void Player::verticalCollisionEnter(const physics::ICollidable& col)
{
    physics::RigidBody::verticalCollisionEnter(col);
    if(col.getPosition().y >= getPosition().y)
        canJump=true; //can jump if the player touch the ground
}*/

void Player::collisionEnter(const physics::ICollidable& col, sf::FloatRect collision)
{
    physics::RigidBody::collisionEnter(col, collision);
    if(collision.width > collision.height && collision.top == col.getGlobalBounds().top && acceleration.y < .0f)
    {
        /*std::cout << "I CAN JUMP BECAUSE : collision:";
        Debugger::print(collision); std::cout << " on "; Debugger::print(col.getGlobalBounds());
        std::cout << std::endl;*/
        //Game::setPause(true);
        canJump=true; //can jump if the player touch the ground
    }
}

void Player::updatePhysics(_Float32 dt)
{
    //if(acceleration.y<=0) acceleration.y -= jumpSpeed*dt;  //gravity
    if (acceleration.y != 0)
    {
        if (acceleration.y > 0)
            apexJumpTime += dt;

        //acceleration.y = std::clamp(acceleration.y*dt, -(float)_TILE_HEIGHT, (float)_TILE_HEIGHT)/dt; //todo veloticity maximum par rapport à dt

        if (apexJumpTime > 0.3 /*apex*/)
        {
            acceleration.y = jumpSpeed*-.7f;
            apexJumpTime = 0;
        }
        //TODO gravity
    }
    if(!onGround && acceleration.y<=0) acceleration.y = jumpSpeed*-.7f;
    physics::RigidBody::updatePhysics(dt);

    //std::cout << "yAccel = " << yAcceleration << std::endl;
}

void Player::update(_Float32 dt)
{
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
        jumpSound.play();
        acceleration.y = jumpSpeed;
        canJump = false;
    }

    sprite->update(dt);
    physics::RigidBody::update(dt);
    
    if(life<=0 || (!game.scene.level.globalBounds.intersects(sprite->getGlobalBounds())))
    {
        life = 0;
        Event death;
        death.type = Event::DEATH;
        //sprite->setState(resources::ResourcesManager::PlayerState::dieR);
        game.addEvent(death);
    }

    //std::cout << "Life : " << life << std::endl;
}