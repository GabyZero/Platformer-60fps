#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <SFML/Graphics.hpp>

class Player : public sf::Drawable{
    private:
        float speed = 150.0f; //todo const
        float jumpSpeed = 300.0f; // todo const

        _Float32 yAcceleration = 0.0f;

    public:
        /** attributes **/

        /*sf::Texture texture;*/
        sf::Sprite sprite;

        enum State { left, right, jump, iddle};

        State state;

        /** constructor **/

        Player();
        void initPlayer();
        /** Method **/

        /** sf::Drawable implementaion **/
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

        void updatePhysics(_Float32);
        void update(_Float32);
};

#endif