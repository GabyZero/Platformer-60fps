#include "graphics/statesprite.hpp"

namespace graphics{

AnimatedStateSprite::AnimatedStateSprite(const StateAnimation& sAnim):
IStateSprite(sAnim.nbAnims),AnimatedSprite(*sAnim.animations[0])
{
    for(int i=0;i<nbStates;++i)
    {
       states[i] = sAnim.animations[i];
    }
}

void AnimatedStateSprite::setState(int s)
{
    animation = states[s];
}


}//namespace graphics