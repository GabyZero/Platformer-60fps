#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "graphics/statesprite.hpp"
#include "physics/rigidbody.hpp"

class Game;

class Player : public physics::RigidBody{
    private:
        float speed = 150.0f; //todo const
        float jumpSpeed = 300.0f ; // todo const
        //TODO: max velocity
        float apexJumpTime = .0f;

        /** sounds **/
        sf::Sound jumpSound;



    protected:
        /** rigid body **/
        virtual void setPosition(float,float);
        virtual void setPosition(sf::Vector2f);
        virtual void setX(float);
        virtual void setY(float);

    public:
        /** attributes **/

        Game& game;

        /*sf::Texture texture;*/
        graphics::AnimatedStateSprite* sprite;

        enum State { left, right, jump, iddleL, iddleR, death};

        State state;

        // _Float32 yAcceleration = 0.0f;
        bool canJump = false;

        int life, maxLife;

        /** constructor **/

        Player(Game& game);
        void initPlayer();
        /** Method **/

        /** sf::Drawable implementaion **/
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

        /** ICollidable implementation **/
        virtual const sf::Vector2f& getPosition() const;
        virtual sf::FloatRect getGlobalBounds() const;

        /** Rigidbody **/
        //virtual void verticalCollisionEnter(const ICollidable&);
        virtual void collisionEnter(const ICollidable &collidable, sf::FloatRect collision);
      

        void stopJumping();

        virtual void updatePhysics(_Float32);
        virtual void update(_Float32);
};

#endif