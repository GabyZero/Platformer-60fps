#include "scene.hpp"

Scene::Scene()
{

}

void Scene::initScene()
{
    background.setImage("background.png");


}

void Scene::updatePhysics(_Float32 dt)
{
    player.updatePhysics(dt);
    level.updatePhysics(dt);
}

void Scene::update(float dt)
{
    player.update(dt);
    level.update(dt);
}

void Scene::render(sf::RenderWindow& window)
{
    window.draw(background);
    window.draw(player);
}

Scene::~Scene()
{

}