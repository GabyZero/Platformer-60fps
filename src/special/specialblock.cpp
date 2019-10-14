#include "special/specialblock.hpp"

namespace special
{

    SpecialBlock::SpecialBlock(sf::Sprite _sprite, IComportment& _comportment):
    sprite(_sprite), comportment(_comportment)
    {

    }

    /** ICollidable implementation **/
    
    void SpecialBlock::collisionEnter(const ICollidable &collidable, sf::FloatRect collision)
    {
        comportment(collidable, collision);
    }

    const sf::Vector2f &SpecialBlock::getPosition() const
    {
        return sprite.getPosition();
    }

    sf::FloatRect SpecialBlock::getGlobalBounds() const
    {
        return sprite.getGlobalBounds();
    }

    void SpecialBlock::draw(sf::RenderTarget &target, sf::RenderStates states) const
    {
        target.draw(sprite, states);
    }

    /** end ICollidable implementation **/

} // namespace special