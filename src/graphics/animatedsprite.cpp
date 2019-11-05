#include "graphics/animatedsprite.hpp"

namespace graphics
{

AnimatedSprite::AnimatedSprite(const Animation& _animation):
animation(&_animation)
{
    currentFrame = 0;
    clock = sf::seconds(0);
    setTexture(animation->texture);
    updateSprite(); //initialize the sprite
}

void AnimatedSprite::updateSprite()
{
    int x = animation->width*(currentFrame%animation->nbFrames.x) + animation->offset_w;
    int y = animation->height*(currentFrame/animation->nbFrames.x) + animation->offset_h;
    setTextureRect({x,y,
                    animation->width,
                    animation->height});
}

void AnimatedSprite::resetAnim()
{
    currentFrame = 0;
    clock = clock.Zero;
    updateSprite();
}


void AnimatedSprite::update(float dt)
{
    if(!isPlaying) return;
    clock += sf::seconds(dt);
    if(clock>= animation->frameTime)
    {
        //reset timer without loosing time
        clock -= animation->frameTime;

        if(currentFrame +1 < (animation->nbFrames.x * animation->nbFrames.y))
        {
            //next frame
            currentFrame++;
        }
        else
        {
            if(animation->loop)
            {
                //loop
                currentFrame=0;
            }
            else
            {
                isPlaying=false;
                //currentFrame=0;
            }
            
        }
        
        updateSprite();
    }
}

/*void AnimatedSprite::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(*this, states);
}*/

} // namespace graphics
