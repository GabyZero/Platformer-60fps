#include "game.hpp"

Game::Game():
window(sf::VideoMode(_WIDTH, _HEIGHT), _GAMENAME),
scene()
{

}

void Game::initGame()
{
    scene.initScene();
}

Game::~Game()
{
    
}