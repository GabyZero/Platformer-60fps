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

            texture = sf::Texture();
            texture.loadFromFile(path+"background.png");
            textures.addAsset("background",texture);

            texture = sf::Texture();
            texture.loadFromFile(path+"block.png");
            textures.addAsset("block",texture);
        }catch(std::exception e)
        {
            std::cerr << e.what() << std::endl;
            exit(1);
        }
    }

    void ResourcesManager::loadResources()
    {
        loadTextures();
    }

}