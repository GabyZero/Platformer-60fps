#ifndef ASSETSMANAGER_HPP
#define ASSETSMANAGER_HPP

#include <SFML/Graphics.hpp>
#include <unordered_map>

namespace resources{
    
    template<typename KEY, typename TASSET>
    class AssetsManager{
        private:
            std::unordered_map<KEY, TASSET> assets;

            class AssetsManagerException : public std::exception{
                virtual const char* what() const throw()
                {
                    return "AssetsManagerError";
                }
            };

        public:
            AssetsManager(){}

            void addAsset(const KEY & id, TASSET asset)
            {
                if(!assets.emplace(id, asset).second)
                    throw AssetsManagerException();
            }

            const TASSET& getAsset(const KEY id) const
            {
                return assets.at(id);
            }

            ~AssetsManager(){}
    
    };

    
}

#endif