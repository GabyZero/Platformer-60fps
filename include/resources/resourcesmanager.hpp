#ifndef RESSOURCESMANAGER_HPP
#define RESSOURCESMANAGER_HPP

#include "graphics/animation.hpp"
#include "graphics/stateanimation.hpp"
#include "assetsmanager.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

namespace resources{
    class ResourcesManager{
        protected:
            ResourcesManager();
            ~ResourcesManager();

            void loadTextures();
            void loadTileSet();
            void loadAnimation();
            void loadStateAnimation();
            void loadAudios();
        public:

            /** static instance in the method **/
            static ResourcesManager& instance();

            void loadResources();


            AssetsManager<std::string, sf::Texture> textures;

            /**name => animation **/
            AssetsManager<std::string, graphics::Animation> animations;
            
            enum PlayerState{runL,runR,walkL,walkR,iddleL,iddleR};
            AssetsManager<std::string, graphics::StateAnimation> stateAnimations; //todo: delete memory

            /** id => pair rect, tileset name **/
            AssetsManager<int, std::pair<sf::IntRect,std::string>> mapTileSet;   

            /** id => music **/  
            AssetsManager<std::string, sf::Music> musics;

            /** id => soundbuffer **/
            AssetsManager<std::string, sf::SoundBuffer> sounds; 


    };
}

#endif
