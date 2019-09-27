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

            AssetsManager<sf::Texture> textures;            


    };
}

#endif
