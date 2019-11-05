#include "game.hpp"

#include "resources/resourcesmanager.hpp"

#include <iostream>

bool Game::pause = false;

Game::Game():
window(sf::VideoMode(_WIDTH, _HEIGHT), _GAMENAME, sf::Style::Titlebar|sf::Style::Close),
view(sf::FloatRect(0,0,_CAMERA_WIDTH,_CAMERA_HEIGHT)),
scene(*this)
{
    resources::ResourcesManager::instance().loadResources();
    window.setView(view);
}

void Game::addEvent(Event& evt)
{
    eventList.push(evt);
}

void Game::manageEvents()
{
    while(!eventList.empty())
    {
        handleEvent(eventList.front());
        eventList.pop();
    }
    loading=false;
}

void Game::handleEvent(Event& evt)
{
    std::cout << "Handling an event" << std::endl;
    switch(evt.type)
    {
        case Event::EventType::PLAYER_DAMAGE:
            scene.player.life -= evt.playerDamage.damage;
            break;
        case Event::EventType::LEVEL_END:
            if(loading)break;
            loading=true;
            if(!scene.level.initLevel(++level))
                window.close();
            break;
        case Event::DEATH:
            scene.level.initLevel(level);
            scene.player.life = scene.player.maxLife;
            break;
        default:
            throw std::runtime_error("Event not handled");
    }
}

void Game::setPause(bool p)
{
    pause = p;
}

void Game::initGame()
{
    scene.initScene();
    ui.initGameUI();
}

Game::~Game()
{
    window.close();
}