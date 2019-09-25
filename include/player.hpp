#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <SFML/Graphics.hpp>

class Player : public sf::Drawable{
    private:
        float speed = 75.0f; //todo const
        float jumpSpeed = 150.0f; // todo const

        _Float32 yAcceleration = 0.0f;

    public:
        /** attributes **/

        sf::Texture texture;
        sf::Sprite sprite;

        enum State { left, right, jump, iddle};

        State state;

        /** constructor **/

        Player();

        /** Method **/

        /** sf::Drawable implementaion **/
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

        void UpdatePhysics(_Float32);
        void Update(_Float32);
};

#endif