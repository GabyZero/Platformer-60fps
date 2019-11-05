#ifndef SPECIALBLOCKFACTORY_HPP
#define SPECIALBLOCKFACTORY_HPP

#include "special/icomportment.hpp"
#include "special/specialblock.hpp"
#include "movingblock.hpp"

namespace special {

    class SpecialBlockFactory{
        private:
            SpecialBlockFactory();

        public:
            enum SpecialBlockID{FIRE,BEGIN,END,CASTLE,MOVINGUP2,MOVINGLEFT2};

            // return the pair {pointer to the block, boolean isCollidable}
            static std::pair<Block*,bool> getBlock(int id, Game& game)
            {
                switch (id)
                {
                case _BEGIN_SPECIALTILE+SpecialBlockID::FIRE:
                    return {getFlame(game), false};
                
                case _BEGIN_SPECIALTILE+SpecialBlockID::END:
                    return {getEnd(game),false};
                case _BEGIN_SPECIALTILE+SpecialBlockID::CASTLE:
                    return {getCastle(), false};
                case _BEGIN_SPECIALTILE+SpecialBlockID::MOVINGUP2:
                    return {getMovingBlockUp2(),true};
                case _BEGIN_SPECIALTILE+MOVINGLEFT2:
                    return {getMovingBlockLeft2(),true};
                default:
                    std::cout << "Error while getting special block " + id << std::endl;
                    return {getFlame(game),true};
                }
            }
            static SpecialBlock<AnimatedBlock> *getFlame(Game &);
            static SpecialBlock<Block> *getEnd(Game&);
            static AnimatedBlock* getCastle();
            static MovingBlock* getMovingBlockUp2();
            static MovingBlock* getMovingBlockLeft2();
        
    };
}

#endif