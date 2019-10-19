#ifndef STATE_SPRITE
#define STATE_SPRITE

#include <SFML/Graphics.hpp>
#include "graphics/animatedsprite.hpp"
#include "graphics/stateanimation.hpp"

namespace graphics{

template<typename T>
class IStateSprite
{
    protected:
        const T** states;
        const int nbStates;
    public:
        IStateSprite(int _nbStates):nbStates(_nbStates)
        {
            states = new const T*[nbStates];
        }

        ~IStateSprite()
        {
            delete[] states;
        }

        void initState(int n, const T* s)
        {
            if(n<nbStates)
            {
                states[n] = s;
            }
            else throw "Error initState";
        }
        
        virtual void setState(int) = 0;
};

class StateSprite : public sf::Sprite, public IStateSprite<sf::Texture>
{   
    //todo    
};


class AnimatedStateSprite : public AnimatedSprite,  public IStateSprite<Animation>
{
    public:
        AnimatedStateSprite(const StateAnimation&);
        virtual void setState(int);


};

}

#endif