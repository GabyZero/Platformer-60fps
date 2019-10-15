#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Graphics.hpp>

#include "scene.hpp"

#define _FPS 60
#define _WIDTH 800
#define _HEIGHT 800
#define _CAMERA_WIDTH 250
#define _CAMERA_HEIGHT 250
#define _GAMENAME "Plaformer random v0"

#define _TILE_WIDTH 16
#define _TILE_HEIGHT 16




/**
 * Main class of the game, will run the game loop
 **/
class Game{
    
    protected:      
        sf::RenderWindow window;
        sf::View view;

    public:
        Scene scene;

        Game();

        void initGame();   

        /** Game loop, to be implemented**/
        virtual void run() = 0;

        virtual ~Game();

};

#endif