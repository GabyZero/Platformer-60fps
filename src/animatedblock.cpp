#include "animatedblock.hpp"

AnimatedBlock::AnimatedBlock(const graphics::Animation& _animation)
{
    sprite = new graphics::AnimatedSprite(_animation);
    //sprite->setScale(_TILE_WIDTH/_animation.width,_TILE_HEIGHT/_animation.height); 
}

void AnimatedBlock::update(float dt)
{
    dynamic_cast<graphics::AnimatedSprite*>(sprite)->update(dt);
}