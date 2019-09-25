#include "scene.hpp"

Scene::Scene()
{

}

void Scene::initScene()
{
    background.setImage("background.png");
}

void Scene::UpdatePhysics(_Float32 dt)
{
    player.UpdatePhysics(dt);
}


void Scene::render(sf::RenderWindow& window)
{
    window.draw(background);
    window.draw(player);
}

Scene::~Scene()
{

}