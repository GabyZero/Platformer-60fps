#ifndef SPECIALBLOCK_HPP
#define SPECIALBLOCK_HPP

#include <SFML/Graphics.hpp>

#include "graphics/animation.hpp"
#include "special/icomportment.hpp"
#include "physics/icollidable.hpp"
#include "block.hpp"
#include "animatedblock.hpp"

namespace special{

/** Collidable block with special comportment **/
template<class TBLOC>
class SpecialBlock : public TBLOC{
    private:
        IComportment* comportment;
    
    public:
        /** constructor for animated block **/
        SpecialBlock(const graphics::Animation& _animation, IComportment* _comportment):
    AnimatedBlock(_animation),comportment(_comportment)
    {
    }


        /** constructor for block not animated **/
        SpecialBlock(sf::IntRect &_rect, const sf::Texture & _text,IComportment* _comportment):
    Block(_rect,_text),comportment(_comportment)
    {

    }

    ~SpecialBlock()
    {
        delete comportment;
    }

        /** ICollidable implementation **/
        virtual void collisionEnter(const physics::ICollidable &collidable, sf::FloatRect collision)
    {
        (*comportment)(collidable, collision);
    }
        /** end ICollidable **/
};
}

#endif