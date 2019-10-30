#ifndef GAME_HPP
#define GAME_HPP

#include <queue>
#include <exception>

#include <SFML/Graphics.hpp>

#include "scene.hpp"
#include "event.hpp"
#include "ui/uimanager.hpp"

#define _FPS 20
#define _WIDTH 800
#define _HEIGHT 800
#define _CAMERA_WIDTH 333
#define _CAMERA_HEIGHT 333
#define _GAMENAME "Plaformer random v0"

#define _PLAYER_MAXLIFE 100
#define _PLAYER_WIDTH 20
#define _PLAYER_HEIGHT 20

#define _TILE_WIDTH 16
#define _TILE_HEIGHT 16


/**
 * Main class of the game, will run the game loop
 **/
class Game{
    
    protected:      
        sf::RenderWindow window;
        sf::View view;

        std::queue<Event> eventList;
        
        static bool pause;

    public:
        Scene scene;
        ui::UIManager ui;
        
        Game();

        void initGame();   

        void addEvent(Event&);
        void manageEvents();
        void handleEvent(Event&);


        static void setPause(bool);
        /** Game loop, to be implemented**/
        virtual void run() = 0;

        virtual ~Game();

};

#endif