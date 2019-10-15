#ifndef BLOCK_HPP
#define BLOCK_HPP

#include <SFML/Graphics.hpp>

#include "physics/icollidable.hpp"
#include "game.hpp"

class Block : public physics::ICollidable
{
protected:
    sf::Sprite* sprite;

public:
    Block();
    Block(sf::IntRect &, const sf::Texture &);

    ~Block();

    /** sf::Drawable implementaion **/
    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;

    /** ICollidable implementation **/
    virtual void collisionEnter(const ICollidable &collidable, sf::FloatRect collision);
    virtual const sf::Vector2f& getPosition() const;
    virtual sf::FloatRect getGlobalBounds() const;
    virtual void update(float);
    /** end ifcollidable**/

    void setPosition(float x, float y);

};

#endif