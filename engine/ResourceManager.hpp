#ifndef RESOURCEMANAGER_HPP
#define RESOURCEMANAGER_HPP

#include <map>
#include <SFML/Graphics.hpp>
#include <SFML/System/NonCopyable.hpp>
#include <memory>
#include <cassert>
#include <Box2D/Box2D.h>
#include "ResourceManagerImpl/ResourceKeys.hpp"
#include "Globals.hpp"

namespace
{
    typedef std::string ID;
}

template <typename Param>
class PointerHolder : sf::NonCopyable
{
    public:
        std::shared_ptr <Param> load(const ID& name, const thor::ResourceKey <Param>& key)
        {
            m_resourcePointers[name] = m_resourceCache.acquire(key);
            m_resourceKeys.insert(std::make_pair(name, key));
            return get(name);
        }

        std::shared_ptr <Param> get (const ID& name)
        {
            auto found = m_resourceKeys.find(name);
            assert(found != m_resourceKeys.end());
            return m_resourceCache.acquire(found->second);
        }

        void release(const ID& name)
        {
            auto keyFound = m_resourceKeys.find(name);

            if (keyFound == m_resourceKeys.end())
                return;

            m_resourceCache.release(keyFound->second);
            m_resourceKeys.erase(keyFound);
            auto ptrFound = m_resourcePointers.find(name);
            assert(ptrFound != m_resourcePointers.end());
            m_resourcePointers.erase(ptrFound);
        }

    private:
        thor::ResourceCache <Param>              m_resourceCache;
        std::map <ID, std::shared_ptr <Param>>   m_resourcePointers;
        std::map <ID, thor::ResourceKey <Param>> m_resourceKeys;
};

class ResourceManager : sf::NonCopyable
{
    public:
        template <typename Param>
        inline std::shared_ptr <Param> load(const ID& name, const thor::ResourceKey <Param>& key);
        inline tmx::MapLoader* loadTileMap(const ID& name, const std::string& mapname);
        inline b2World* createWorld(int gravx, int gravy);

        template <typename Param>
        inline std::shared_ptr <Param> get(const ID& name);

        template <typename Param>
        inline void release(const ID& name);

    private:
        PointerHolder <sf::Texture>    m_textureHolder;
        PointerHolder <tgui::Gui>      m_guiHolder;
        PointerHolder <sf::Shader>     m_shaderHolder;
        PointerHolder <sf::Font>       m_fontHolder;
        PointerHolder <tmx::MapLoader> m_mapHolder;

        std::shared_ptr <b2World>      m_worldHolder;
};

#include "ResourceManagerImpl/Load.inl"
#include "ResourceManagerImpl/Get.inl"
#include "ResourceManagerImpl/Release.inl"

#endif
