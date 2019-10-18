#include "animatedblock.hpp"

#include <iostream>

AnimatedBlock::AnimatedBlock(const graphics::Animation& _animation)
{
    sprite = new graphics::AnimatedSprite(_animation);
    sprite->setScale(_TILE_WIDTH/static_cast<float>(_animation.width),_TILE_HEIGHT/static_cast<float>(_animation.height)); 
}

void AnimatedBlock::update(float dt)
{
    dynamic_cast<graphics::AnimatedSprite*>(sprite)->update(dt);
}