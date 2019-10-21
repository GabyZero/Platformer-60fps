#include "game.hpp"

#include "resources/resourcesmanager.hpp"

#include <iostream>

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
}

void Game::handleEvent(Event& evt)
{
    switch(evt.type)
    {
        case Event::EventType::PLAYER_DAMAGE:
            scene.player.life -= evt.playerDamage.damage;
            break;
        default:
            throw std::runtime_error("Event not handled");
    }
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