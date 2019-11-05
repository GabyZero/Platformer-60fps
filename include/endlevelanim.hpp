#ifndef ENDLEVELANIM_HPP
#define ENDLEVELANIM_HPP

#include <SFML/System.hpp>

class EndLevelAnim
{
    private:
        sf::Time clock = sf::Time::Zero;

    public:
        void init()
        {
            clock = sf::Time::Zero;
            state=MOVING;
        }

        void update(float dt)
        {
            clock += sf::seconds(dt);

            if(clock >= sf::seconds(3.5) && clock <= sf::seconds(4.5))
                state=WAIT;
            else if(clock >= sf::seconds(4.5))
                state=GO;
        }


        enum ELAState{MOVING,EXPLOSION,WAIT,GO};
        ELAState state = MOVING;
};

#endif