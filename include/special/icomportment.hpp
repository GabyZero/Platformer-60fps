#ifndef ICOMPORTMENT_HPP
#define ICOMPORTMENT_HPP

#include <SFML/Graphics.hpp>

#include "physics/icollidable.hpp"

namespace special {

    /** Interface of the functional objects for special block **/
    class IComportment{
        public:
            virtual void operator()(const physics::ICollidable &collidable, sf::FloatRect collision) = 0;
    };

    /** comportment, every character collided shall die **/
    class ComportmentDie : public IComportment{
        public:
            virtual void operator()(const physics::ICollidable &collidable, sf::FloatRect collision);
    };

}

#endif