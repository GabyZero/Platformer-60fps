#include "resources/resourcesmanager.hpp"

#include <iostream>
#include <cstring>

namespace resources{

    ResourcesManager::ResourcesManager()
    {

    }

    ResourcesManager::~ResourcesManager()
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
            sf::Texture* texture = new sf::Texture();
            texture->loadFromFile(path+"player.png");
            textures.addAsset("player",texture);

            /** background **/
            texture = new sf::Texture();
            texture->loadFromFile(path+"sky.jpg");
            texture->setRepeated(true);
            textures.addAsset("sky", texture);

            /** adds **/
            texture = new sf::Texture();
            texture->loadFromFile(path+"block.png");
            textures.addAsset("block",texture);

            /** tilesets **/
            texture = new sf::Texture();
            texture->loadFromFile("resources/maps/tileset_1.png");
            textures.addAsset("tileset1",texture);

            texture = new sf::Texture();
            texture->loadFromFile("resources/maps/tileset_2.png");
            textures.addAsset("tileset2",texture);

            /** animation **/
            texture = new sf::Texture();
            texture->loadFromFile(path+"animations/fire.png");
            textures.addAsset("fire",texture);

            texture = new sf::Texture();
            texture->loadFromFile(path+"player/player.png");
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
        std::pair<sf::IntRect, std::string> *pair;
        for(int y = 0 ; y < height; y += size)
        {
            for(int x = 0 ; x < width ; x += size)
            {
                pair = new std::pair<sf::IntRect,std::string>(sf::IntRect(x,y,size,size), std::string("tileset1"));
                mapTileSet.addAsset(id++, pair);
            }
        }

        /* second same size */
        for(int y = 0 ; y < height; y += size)
        {
            for(int x = 0 ; x < width ; x += size)
            {
                //std::cout << id << std::endl;
                pair = new std::pair<sf::IntRect,std::string>(sf::IntRect(x,y,size,size), std::string("tileset2"));
                mapTileSet.addAsset(id++, pair);
            }
        }
        std::cout << "Tileset loaded" << std::endl;
    }

    void ResourcesManager::loadAnimation()
    {
        graphics::Animation *animation = new graphics::Animation(32,32,0,0,textures.getAsset("fire"), 3);
        animations.addAsset("fire",animation);

        std::cout << "Animation loaded" << std::endl;
    }
    void ResourcesManager::loadStateAnimation()
    {
        graphics::StateAnimation *anims = new graphics::StateAnimation(6);
        const sf::Texture &t = textures.getAsset("playerA");


        anims->animations[PlayerState::iddleL] = new graphics::Animation(17,22,0,0,t,2,sf::seconds(0.9f)); //iddleL
        anims->animations[PlayerState::iddleR] = new graphics::Animation(17,22,0,24,t,2,sf::seconds(0.9f)); //iddleR
        
        anims->animations[PlayerState::walkL] = new graphics::Animation(17,22,42,0,t,4,sf::seconds(0.2f)); //walkL
        anims->animations[PlayerState::walkR] = new graphics::Animation(17,22,42,24,t,4,sf::seconds(0.1f)); //walkR
        
        anims->animations[PlayerState::runL] = new graphics::Animation(17,22,102,0,t,4,sf::seconds(0.15f)); //runL
        anims->animations[PlayerState::runR] = new graphics::Animation(17,22,102,24,t,4,sf::seconds(0.15f)); //runR

        stateAnimations.addAsset("player", anims);

        std::cout << "State animation loaded" << std::endl;
    }

    void ResourcesManager::loadAudios()
    {
        std::string path = "resources/audio/";
        
        sf::Music* music = new sf::Music();
        if(!music->openFromFile(path+"music/music1.ogg"))
        {
            std::cerr << "can't open " << path+"music/music1.ogg" << std::endl;
        }
        music->setVolume(60);
        music->setLoop(true);

        musics.addAsset("music1", music);

        /** Sound effect **/
        sf::SoundBuffer* sb = new sf::SoundBuffer();
        if(!sb->loadFromFile(path+"sound/jump1.ogg"))
            std::cerr << "can't open" << path+"sound/jump1.ogg";

        sounds.addAsset("jump1",sb);

        std::cout << "Audio loaded" << std::endl;

    }

    void ResourcesManager::loadResources()
    {
        loadTextures();
        loadTileSet();
        loadAnimation();
        loadStateAnimation();
        loadAudios();

        std::cout << "Resources loaded" << std::endl;
    }

}