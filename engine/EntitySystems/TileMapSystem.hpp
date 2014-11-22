#ifndef TILEMAPSYSTEM_HPP
#define TILEMAPSYSTEM_HPP

#include <tmx/MapLoader.h>
#include <entityx/entityx.h>

#include "../Globals.hpp"
#include "BasicSystem.hpp"

class TileMapSystem : public entityx::System <TileMapSystem>, public BasicSystem
{
public:
    void update(entityx::EntityManager &es, entityx::EventManager &events, entityx::TimeDelta dt)
    {

    }

    void setTileMap(tmx::MapLoader* map)
    {
        /*here parse all map, layer and object properties, add box2d bodies etc.*/
        m_tileMap = map;
        auto& layers = map->GetLayers();

        for (auto& layer : layers)
        {
            if (layer.type == tmx::ObjectGroup)
            {
                for (auto& object : layer.objects)
                {
                    if (object.GetPropertyString("entity") == "true")
                    {
                        luabridge::LuaRef createEntityF = global.vgbLuaNamespace["createEntityF"];
                        entityx::Entity ent = createEntityF(object.GetPropertyString("entity_name"));
                        /*here set the box2d body and the sprite position/ code below is temporary*/
                        GraphicsComponent::Handle handle = ent.component <GraphicsComponent> ();

                        if (handle)
                        {
                            handle->sprite.setPosition(object.GetPosition());
                        }
                    }
                }
            }
        }
    }

    tmx::MapLoader* getTileMap() const
    {
        return m_tileMap;
    }

private:
    tmx::MapLoader* m_tileMap;
};

#endif