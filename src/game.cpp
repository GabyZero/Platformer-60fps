#include "game.hpp"

#include "resources/resourcesmanager.hpp"

Game::Game():
window(sf::VideoMode(_WIDTH, _HEIGHT), _GAMENAME, sf::Style::Titlebar|sf::Style::Close)
{
    resources::ResourcesManager::instance().loadResources();
}

void Game::initGame()
{
    scene.initScene();
}

Game::~Game()
{
    
}