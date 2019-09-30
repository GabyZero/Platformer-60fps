#ifndef RESSOURCESMANAGER_HPP
#define RESSOURCESMANAGER_HPP

#include "assetsmanager.hpp"

namespace resources{
    class ResourcesManager{
        protected:
            ResourcesManager();

            void loadTextures();

        public:

            /** static instance in the method **/
            static ResourcesManager& instance();

            void loadResources();
            void loadTileSet();

            AssetsManager<std::string, sf::Texture> textures;  

            /** id => pair rect, tileset name **/
            AssetsManager<int, std::pair<sf::IntRect,std::string>> mapTileSet;          


    };
}

#endif
