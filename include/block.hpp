#ifndef BLOCK_HPP
#define BLOCK_HPP

#include <SFML/Graphics.hpp>

#include "physics/icollidable.hpp"

class Block : public physics::ICollidable
{
private:
    sf::Sprite sprite;

public:
    Block(sf::IntRect &, const sf::Texture &);

    /** sf::Drawable implementaion **/
    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;

    /** ICollidable implementation **/
    virtual void collisionEnter(const ICollidable &collidable, sf::FloatRect collision);
    virtual const sf::Vector2f& getPosition() const;
    virtual sf::FloatRect getGlobalBounds() const;

    void setPosition(float x, float y);

};

#endif