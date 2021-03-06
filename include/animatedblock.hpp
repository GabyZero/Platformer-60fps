#ifndef ANIMATEDBLOCK_HPP
#define ANIMATEDBLOCK_HPP

#include "block.hpp"
#include "graphics/animatedsprite.hpp"

class AnimatedBlock : public Block{
    public:
        AnimatedBlock(){}
        AnimatedBlock(const graphics::Animation&,bool scalable=true);

        virtual void update(float) override;

        void setPlaying(bool);
    
};

#endif