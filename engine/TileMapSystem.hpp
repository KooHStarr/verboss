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
    void m_addComplexDynamicBody(tmx::MapObject& object, b2World* world, PhysicsComponent::Handle phandle);
    void m_addComplexStaticBody(tmx::MapObject& object, b2World* world, PhysicsComponent::Handle phandle, entityx::Entity ent);
    void m_addName(entityx::Entity ent, tmx::MapObject& object);


private:
    tmx::MapLoader* m_tileMap;
};

#endif