#ifndef ASSETSMANAGER_HPP
#define ASSETSMANAGER_HPP

#include <unordered_map>

namespace resources{
    
    class AssetsManagerException : public std::exception{
        virtual const char* what() const throw()
        {
            return "AssetsManagerError";
        }
     };

    template<typename KEY, typename TASSET>
    class AssetsManager{
        private:
            std::unordered_map<KEY, TASSET*> assets;
            

        public:

            AssetsManager(){}
            ~AssetsManager()
            {
                for(auto p : assets)
                {
                    delete p.second;
                }
            }

            void addAsset(const KEY & id, TASSET *asset)
            {
                if(!assets.emplace(id, std::move(asset)).second)
                    throw AssetsManagerException();
            }

            const TASSET& getAsset(const KEY id) const
            {   
                try{
                    return *assets.at(id);
                }catch(std::out_of_range)
                {
                    throw AssetsManagerException();
                }
            }

            TASSET& getAsset(const KEY id)
            {   
                try{
                    return *assets.at(id);
                }catch(std::out_of_range)
                {
                    throw AssetsManagerException();
                }
            }

    
    };

    
}

#endif