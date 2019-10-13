#include "resources/resourcesmanager.hpp"

#include <iostream>

namespace resources{

    ResourcesManager::ResourcesManager()
    {

    }

    ResourcesManager& ResourcesManager::instance()
    {
        static ResourcesManager instance;
        return instance;
    }

    void ResourcesManager::loadTextures()
    {
        std::string path = "resources/textures/";
        try{
            sf::Texture texture;
            texture.loadFromFile(path+"player.png");
            textures.addAsset("player",texture);

            /** background **/
            texture = sf::Texture();
            texture.loadFromFile(path+"sky.jpg");
            texture.setRepeated(true);
            textures.addAsset("sky",texture);

            /** adds **/
            texture = sf::Texture();
            texture.loadFromFile(path+"block.png");
            textures.addAsset("block",texture);

            /** tilesets **/
            texture = sf::Texture();
            texture.loadFromFile("resources/maps/tileset_1.png");
            textures.addAsset("tileset1",texture);

            texture = sf::Texture();
            texture.loadFromFile("resources/maps/tileset_2.png");
            textures.addAsset("tileset2",texture);

            /** animation **/
            texture = sf::Texture();
            texture.loadFromFile(path+"animations/fire.png");
            textures.addAsset("fire",texture);
        }catch(std::exception e)
        {
            std::cerr << e.what() << std::endl;
            exit(1);
        }
        std::cout << "Texture loaded" << std::endl;
    }

    void ResourcesManager::loadTileSet()
    {
        /* first */
        int width = 112, height = 96;
        int size = 16;
        
        int id = 0;
        std::pair<sf::IntRect, std::string> pair;
        for(int y = 0 ; y < height; y += size)
        {
            for(int x = 0 ; x < width ; x += size)
            {
                pair = std::pair(sf::IntRect(x,y,size,size), "tileset1");
                mapTileSet.addAsset(id++, pair);
            }
        }

        /* second same size */
        for(int y = 0 ; y < height; y += size)
        {
            for(int x = 0 ; x < width ; x += size)
            {
                std::cout << id << std::endl;
                pair = std::pair(sf::IntRect(x,y,size,size), "tileset2");
                mapTileSet.addAsset(id++, pair);
            }
        }
        std::cout << "Tileset loaded" << std::endl;
    }

    void ResourcesManager::loadAnimation()
    {
        graphics::Animation animation(32,32,0,0,textures.getAsset("fire"), 3);
        animations.addAsset("fire",animation);

        std::cout << "Animation loaded" << std::endl;
    }

    void ResourcesManager::loadResources()
    {
        loadTextures();
        loadTileSet();
        loadAnimation();

        std::cout << "Resources loaded" << std::endl;
    }

}