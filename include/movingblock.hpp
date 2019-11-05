#ifndef MOVINGBLOCK_HPP
#define MOVINGBLOCK_HPP

#include "block.hpp"
#include "physics/rigidbody.hpp"

class MovingBlock : public Block
{
    private:
        int nbBloc;
        sf::Vector2f acceleration;

        sf::Vector2f defaultposition;
    public:
        MovingBlock(sf::IntRect &, const sf::Texture &,int,sf::Vector2f);

        virtual void update(float);
        virtual void updatePhysics(float);

        virtual void setPosition(float x, float y);

};

#endif