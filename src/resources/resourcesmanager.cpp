#include "resources/resourcesmanager.hpp"

#include <iostream>
#include <cstring>

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

            texture = sf::Texture();
            texture.loadFromFile(path+"player/player.png");
            textures.addAsset("playerA", texture);
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
                //std::cout << id << std::endl;
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
    void ResourcesManager::loadStateAnimation()
    {
        graphics::StateAnimation anims(6);
        const sf::Texture &t = textures.getAsset("playerA");


        anims.animations[2] = new graphics::Animation(17,22,0,0,t,2,sf::seconds(0.9f)); //iddleL
        anims.animations[3] = new graphics::Animation(17,22,0,22,t,2,sf::seconds(0.9f)); //iddleR
        
        anims.animations[4] = new graphics::Animation(17,22,42,0,t,4,sf::seconds(0.2f)); //walkL
        anims.animations[5] = new graphics::Animation(17,22,42,23,t,4,sf::seconds(0.1f)); //walkR
        
        anims.animations[1] = new graphics::Animation(17,22,102,0,t,4,sf::seconds(0.1f)); //runL
        anims.animations[0] = new graphics::Animation(17,22,102,22,t,4,sf::seconds(0.15f)); //runR

        stateAnimations.addAsset("player", anims);

        std::cout << "State animation loaded" << std::endl;
    }

    void ResourcesManager::loadResources()
    {
        loadTextures();
        loadTileSet();
        loadAnimation();
        loadStateAnimation();

        std::cout << "Resources loaded" << std::endl;
    }

}