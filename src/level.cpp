#include "level.hpp"

#include "resources/resourcesmanager.hpp"
#include <iostream>
#include <fstream>
#include "block.hpp"

Level::Level()
{}

Level::~Level()
{
    for(physics::ICollidable *col : collidable)
        delete col;
}

void Level::loadMap(const std::string path)
{
    std::ifstream file(path, std::ifstream::in);
    if(file.fail())
    {
        std::cerr << "Error while openning : " << path << std::endl;
        exit(1);
    }

    int size = 16;
    int x = 0, y = 0;

    int id;
    char c;
    while(file.good())
    {
        file >> id;

        if(id!=-1)
        {
            auto pair = resources::ResourcesManager::instance().mapTileSet.getAsset(id);
            //sf::Sprite sprite(resources::ResourcesManager::instance().textures.getAsset(pair.second),pair.first);
            Block* block = new Block(pair.first,resources::ResourcesManager::instance().textures.getAsset(pair.second));
            block->setPosition(x,y);
            //sprite.setPosition(x,y);
            collidable.push_back(block);
            
            std::cout << "id:" << id << " (" << x << "," << y << ")";
            std::cout << " => " << pair.second;
            std::cout << "(" << pair.first.left << "," << pair.first.top << ")[" << pair.first.width << "x" << pair.first.height << "]";
            std::cout << std::endl;
        }
        c = file.peek();
        if(c==',')
        {
            file >> c;
            x+=size;
        }
        else
        {
            //std::cout << "["<<c<<"]"<<std::endl;
            x=0;
            y+=size;
        }       
    }
}

void Level::initLevel()
{
    loadMap("resources/maps/map1.csv");
    /*sf::Sprite sprite(resources::ResourcesManager::instance().textures.getAsset("block"));
    sprite.setPosition(255,200);
    collidable.push_back(std::move(sprite));

    sprite = sf::Sprite(sprite);
    sprite.setPosition(255,280);
    collidable.push_back(std::move(sprite));

    sprite = sf::Sprite(sprite);
    sprite.setPosition(350,255);
    collidable.push_back(std::move(sprite));

    sprite = sf::Sprite(sprite);
    sprite.setPosition(150,255);
    collidable.push_back(std::move(sprite));*/
    
    //** todo: ajout de 4 gros collidable autour du niveau
}

void Level::update(const double)
{

}

void Level::updatePhysics(const double)
{

}

void Level::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    for(physics::ICollidable *col : collidable)
        target.draw(*col, states);

    for(sf::Sprite sp : others)
        target.draw(sp, states);
}