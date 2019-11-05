#ifndef GAME_HPP
#define GAME_HPP

#include <queue>
#include <exception>

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "scene.hpp"
#include "event.hpp"
#include "ui/uimanager.hpp"
#include "audio/audiomanager.hpp"

#define _FPS 60
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

#define _BEGIN_SPECIALTILE 84

#define _GAME_NBLVL 2
constexpr char* _LEVEL_PATH[]= {"map0.json", "map2.json"};


/**
 * Main class of the game, will run the game loop
 **/
class Game{
    
    protected:      
        sf::RenderWindow window;
        std::queue<Event> eventList;
        
        static bool pause;
        bool loading = false; //for the switching of level game.cpp line:32
        int level = 0;

    public:
        sf::View view;

        Scene scene;
        ui::UIManager ui;
        audio::AudioManager audioManager;
        
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