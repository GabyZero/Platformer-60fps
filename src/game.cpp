#include "game.hpp"

Game::Game():
window(sf::VideoMode(_WIDTH, _HEIGHT), _GAMENAME, sf::Style::Titlebar|sf::Style::Close),
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