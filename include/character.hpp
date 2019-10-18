#ifndef CHARACTER_HPP
#define CHARACTER_HPP

#include "physics/icollidable.hpp"

class Character : public physics::ICollidable{
    private:
        sf::Sprite sprite;
        
    public:
        virtual void collisionEnter(const ICollidable &collidable, sf::FloatRect collision) = 0;
        virtual const sf::Vector2f& getPosition() const  = 0 ;
        virtual sf::FloatRect getGlobalBounds() const = 0 ;
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const = 0;
        virtual void update(float) = 0;
};

#endif