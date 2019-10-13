#include "graphics/animatedsprite.hpp"

namespace graphics
{

AnimatedSprite::AnimatedSprite(const Animation& _animation):
animation(_animation)
{
    currentFrame = 0;
    clock = sf::seconds(0);
    sprite.setTexture(animation.texture);
    updateSprite(); //initialize the sprite
}

void AnimatedSprite::updateSprite()
{
    sprite.setTextureRect({animation.width*currentFrame,0,animation.width,animation.height}); // todo: add offset
}

void AnimatedSprite::update(float dt)
{
    clock += sf::seconds(dt);
    if(clock>= animation.frameTime)
    {
        //reset timer without loosing time
        clock -= animation.frameTime;

        if(currentFrame +1 < animation.nbFrames)
        {
            //next frame
            currentFrame++;
        }
        else
        {
            if(animation.loop)
            {
                //loop
                currentFrame=0;
            }
            else
            {
                //todo: stop animation
            }
            
        }
        
        updateSprite();
    }
}

void AnimatedSprite::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(sprite, states);
}

} // namespace graphics
