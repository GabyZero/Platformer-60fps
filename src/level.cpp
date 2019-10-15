#include "level.hpp"

#include "resources/resourcesmanager.hpp"
#include "resources/RSJparser.tcc"
#include <iostream>
#include <fstream>
#include "block.hpp"

#include "game.hpp"

Level::Level(Game& _game):game(_game)
{}

Level::~Level()
{
    for(physics::ICollidable *col : collidable)
        delete col;

    for(physics::ICollidable *col : trigerrable)
        delete col;
}

void Level::loadMap(const std::string path)
{
    std::ifstream file(path, std::ifstream::in);
    std::istream* stream = &file;

    RSJresource rsc = (*stream);
    
    for(int i = 0;;i++)
    {
        if(rsc["layers"][i]["name"].as<std::string>() == "collider")
        {
            int size = _TILE_HEIGHT;//rsc["tileheight"].as<int>();
            int width = rsc["layers"][i]["width"].as<int>();
            int height = rsc["layers"][i]["height"].as<int>();

            game.scene.player.sprite.setPosition(rsc["properties"]["player_pos_x"].as<int>()*size, rsc["properties"]["player_pos_y"].as<int>()*size);

            /** manage background */
            sf::FloatRect rect;
            rect.height = height;
            rect.width = width;

            game.scene.background.setImage(resources::ResourcesManager::instance().textures.getAsset(rsc["properties"]["background"].as<std::string>()));
            game.scene.background.setSize(width*size+(2*_CAMERA_WIDTH), height*size+(2*_CAMERA_HEIGHT));
            /* end background */

            int x = 0, y = 0;

            for(int h=0;h<height;++h)
            {
                for(int w=0;w<width;++w)
                {
                    int id = rsc["layers"][i]["data"][h*width+w].as<int>()-1;
                    if(id>=0)
                    {
                        auto pair = resources::ResourcesManager::instance().mapTileSet.getAsset(id);
                        Block* block = new Block(pair.first,resources::ResourcesManager::instance().textures.getAsset(pair.second));
                        block->setPosition(x,y);
                        collidable.push_back(block);
                    }
                    x+=size;
                }
                y+=size;
                x=0;
            }
            break;
        }
    }

    /*if(file.fail())
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
    }*/
}

void Level::initLevel()
{
    loadMap("resources/maps/map2.json");
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

void Level::update(const double dt)
{
    for(physics::ICollidable *col : collidable)
        col->update(dt);    
    for(physics::ICollidable *col : trigerrable)
        col->update(dt);
}

void Level::updatePhysics(const double)
{

}

void Level::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    for(physics::ICollidable *col : collidable)
        target.draw(*col, states);

    for(physics::ICollidable *col : trigerrable)
        target.draw(*col, states);

    for(sf::Sprite sp : others)
        target.draw(sp, states);
}