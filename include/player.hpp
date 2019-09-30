#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <SFML/Graphics.hpp>

class Player : public sf::Drawable{
    private:
        float speed = 150.0f; //todo const
        float jumpSpeed = 300.0f; // todo const

        float apexJumpTime = .0f;


    public:
        /** attributes **/

        /*sf::Texture texture;*/
        sf::Sprite sprite;

        enum State { left, right, jump, iddle};

        State state;

         _Float32 yAcceleration = 0.0f;


        /** constructor **/

        Player();
        void initPlayer();
        /** Method **/

        /** sf::Drawable implementaion **/
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

        void stopJumping();

        void updatePhysics(_Float32);
        void update(_Float32);
};

#endif