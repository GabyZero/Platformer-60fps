#ifndef STATEANIMATION_HPP
#define STATEANIMATION_HPP

#include "graphics/animation.hpp"

#include <iostream>

namespace graphics
{

struct StateAnimation
{
    Animation** animations;
    const int nbAnims;

    StateAnimation(int nb):nbAnims(nb)
    {
        animations = new Animation*[nb];
    }

    ~StateAnimation()
    {
        //std::cout << "StateAnimation Destructor called with nbAnims=" << nbAnims << std::endl;
        //delete animations;
    }
};

}

#endif