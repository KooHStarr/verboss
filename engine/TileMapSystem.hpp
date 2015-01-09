#ifndef TILEMAPSYSTEM_HPP
#define TILEMAPSYSTEM_HPP

#include <tmx/MapLoader.h>
#include <tmx/tmx2box2d.h>
#include <entityx/entityx.h>

#include "Globals.hpp"
#include "BasicSystem.hpp"
#include "PhysicsSystem.hpp"
#include "InputManager.hpp"
#include "EntityWrapper.hpp"
#include "EntityComponents/CustomPropertyComponent.hpp"
#include "EntityManagerWrapper.hpp"


class TileMapSystem : public entityx::System <TileMapSystem>, public BasicSystem
{
public:
    void update(entityx::EntityManager &es, entityx::EventManager &events, entityx::TimeDelta dt);
    void setTileMap(tmx::MapLoader* map);
    tmx::MapLoader* getTileMap() const;

private:
    void m_addEntityFromFile(tmx::MapObject& object, int layerCount);
    void m_addSimpleEntity  (tmx::MapObject& object);

    void m_attachPhysicsBodyToEntity(tmx::MapObject& object, EntityWrapper entity, b2BodyType type);
    //void m_addComplexDynamicBody(tmx::MapObject& object, EntityWrapper wrapper);
    //void m_addComplexStaticBody (tmx::MapObject& object, EntityWrapper wrapper);

private:
    tmx::MapLoader* m_tileMap;
};

#endif