#include "scene.hpp"

Scene::Scene()
{

}

void Scene::initScene()
{
    background.setImage("background.png");
}

void Scene::render(sf::RenderWindow& window)
{
    window.draw(background);
    window.draw(player);
}

Scene::~Scene()
{

}