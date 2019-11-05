#include "animatedblock.hpp"

#include <iostream>

AnimatedBlock::AnimatedBlock(const graphics::Animation& _animation,bool scalable)
{
    sprite = new graphics::AnimatedSprite(_animation);
    if(scalable) sprite->setScale(_TILE_WIDTH/static_cast<float>(_animation.width),_TILE_HEIGHT/static_cast<float>(_animation.height)); 
    std::cout << "creating animated block with scalable = " << std::boolalpha << scalable << std::endl;
}

void AnimatedBlock::update(float dt)
{
    dynamic_cast<graphics::AnimatedSprite*>(sprite)->update(dt);
}

void AnimatedBlock::setPlaying(bool b)
{
    dynamic_cast<graphics::AnimatedSprite*>(sprite)->isPlaying = b;
}
