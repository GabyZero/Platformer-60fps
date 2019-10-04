#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <SFML/Graphics.hpp>
#include "physics/icollidable.hpp"

class Player : public physics::ICollidable{
    private:
        float speed = 150.0f; //todo const
        float jumpSpeed = 300.0f ; // todo const
        //TODO: max velocity
        float apexJumpTime = .0f;



    public:
        /** attributes **/

        /*sf::Texture texture;*/
        sf::Sprite sprite;

        enum State { left, right, jump, iddle};

        State state;

         _Float32 yAcceleration = 0.0f;
        bool canJump = false;


        /** constructor **/

        Player();
        void initPlayer();
        /** Method **/

        /** sf::Drawable implementaion **/
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

        /** ICollidable implementation **/
        virtual void collisionEnter(const ICollidable &collidable, sf::FloatRect collision);
        virtual const sf::Vector2f& getPosition() const;
        virtual sf::FloatRect getGlobalBounds() const;


        void stopJumping();

        void updatePhysics(_Float32);
        void update(_Float32);
};

#endif