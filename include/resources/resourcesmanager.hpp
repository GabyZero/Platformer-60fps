#ifndef RESSOURCESMANAGER_HPP
#define RESSOURCESMANAGER_HPP

#include "graphics/animation.hpp"
#include "assetsmanager.hpp"

namespace resources{
    class ResourcesManager{
        protected:
            ResourcesManager();

            void loadTextures();
            void loadTileSet();
            void loadAnimation();
        public:

            /** static instance in the method **/
            static ResourcesManager& instance();

            void loadResources();


            AssetsManager<std::string, sf::Texture> textures;

            /**name => animation **/
            AssetsManager<std::string, graphics::Animation> animations;

            /** id => pair rect, tileset name **/
            AssetsManager<int, std::pair<sf::IntRect,std::string>> mapTileSet;          


    };
}

#endif
