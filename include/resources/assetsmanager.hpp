#ifndef ASSETSMANAGER_HPP
#define ASSETSMANAGER_HPP

#include <SFML/Graphics.hpp>
#include <unordered_map>

namespace resources{
    
    template<typename TASSET>
    class AssetsManager{
        private:
            std::unordered_map<std::string, TASSET> assets;

            class AssetsManagerException : public std::exception{
                virtual const char* what() const throw()
                {
                    return "AssetsManagerError";
                }
            };

        public:
            AssetsManager(){}

            void addAsset(const std::string & id, TASSET asset)
            {
                if(!assets.emplace(id, asset).second)
                    throw AssetsManagerException();
            }

            const TASSET& getAsset(const std::string id) const
            {
                return assets.at(id);
            }

            ~AssetsManager(){}
    
    };

    
}

#endif