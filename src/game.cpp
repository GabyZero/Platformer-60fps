#include "game.hpp"

#include "resources/resourcesmanager.hpp"


Game::Game():
window(sf::VideoMode(_WIDTH, _HEIGHT), _GAMENAME, sf::Style::Titlebar|sf::Style::Close),
view(sf::FloatRect(0,0,_CAMERA_WIDTH,_CAMERA_HEIGHT)),
scene(*this)
{
    resources::ResourcesManager::instance().loadResources();
    window.setView(view);   
}

void Game::initGame()
{
    scene.initScene();
}

Game::~Game()
{
    window.close();
}