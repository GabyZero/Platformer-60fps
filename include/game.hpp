#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Graphics.hpp>

#include "scene.hpp"

#define _FPS 60
#define _WIDTH 800
#define _HEIGHT 800
#define _GAMENAME "Plaformer random v0"

/**
 * Main class of the game, will run the game loop
 **/
class Game{
    
    protected:      
        sf::RenderWindow window;
        Scene scene;

    public:
        Game();

        void initGame();   

        /** Game loop, to be implemented**/
        virtual void run() = 0;

        ~Game();

};

#endif