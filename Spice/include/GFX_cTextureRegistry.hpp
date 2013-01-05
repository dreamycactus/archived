#ifndef CTEXTUREREGISTRY_H
#define CTEXTUREREGISTRY_H

#include <unordered_map>
#include <string>
#include "GFX_cTextureWrapper.hpp"

namespace GFX
{
    class cTextureRegistry
    {
    public:
        cTextureRegistry() {}
        virtual ~cTextureRegistry() {}

        static void RegisterTexture(std::string str_key, GFX::cTextureWrapper& tex);
        static cTextureWrapper& GetTexture(std::string str_key);

        static std::unordered_map<std::string, cTextureWrapper> textures_map;

    };
    inline void cTextureRegistry::RegisterTexture(std::string str_key, cTextureWrapper& tex)
    { textures_map.insert(std::pair<std::string, cTextureWrapper>(str_key, tex)); }

    inline cTextureWrapper& cTextureRegistry::GetTexture(std::string str_key)
    { return textures_map[str_key]; }
}


#endif // CTEXTUREREGISTRY_H
