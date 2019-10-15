#ifndef SPECIALBLOCKFACTORY_HPP
#define SPECIALBLOCKFACTORY_HPP

#include "special/icomportment.hpp"
#include "special/specialblock.hpp"

namespace special {

    class SpecialBlockFactory{
        private:
            SpecialBlockFactory();

        public:
            static SpecialBlock getFlame();
        
    };
}

#endif