#ifndef TILEMAPSYSTEM_HPP
#define TILEMAPSYSTEM_HPP

#include <tmx/MapLoader.h>
#include <tmx/tmx2box2d.h>
#include <entityx/entityx.h>

#include "../Globals.hpp"
#include "BasicSystem.hpp"
#include "PhysicsSystem.hpp"
#include "../InputManager.hpp"
#include "../EntityWrapper.hpp"


class TileMapSystem : public entityx::System <TileMapSystem>, public BasicSystem
{
public:
    void update(entityx::EntityManager &es, entityx::EventManager &events, entityx::TimeDelta dt)
    {

    }

    void setTileMap(tmx::MapLoader* map)
    {
        m_tileMap = map;
        auto& layers = map->GetLayers();

        for (auto& layer : layers)
        {
            if (layer.type == tmx::ObjectGroup)
            {
                for (auto& object : layer.objects) {
                    luabridge::LuaRef createEntityF = global.vgbLuaNamespace["createEntityF"];
                    luabridge::LuaRef createEntity = global.vgbLuaNamespace["createEntity"];
                    entityx::Entity ent;
                    EntityWrapper wrap;
                    PhysicsComponent::Handle phandle;
                    b2World *world = m_entityManager->systems.system < PhysicsSystem > ()->getWorld();

                    // create complex entity with box2d body (dynamic or static)
                    if (object.GetPropertyString("entity_name") != "") {
                        wrap = createEntityF(object.GetPropertyString("entity_name"));
                        ent = wrap.getEntity();
                        phandle = ent.component<PhysicsComponent>();

                        if (phandle->configTable["type"] == "dynamic")
                            m_addComplexDynamicBody(object, world, phandle);
                        else
                            m_addComplexStaticBody(object, world, phandle, ent);

                        // create simple entity with static body
                    } else {
                        wrap = createEntity();
                        ent = wrap.getEntity();
                        phandle = ent.assign<PhysicsComponent>();
                        b2Body *body = tmx::BodyCreator::Add(object, *world);
                        phandle->body = body;
                    }

                    if (object.GetPropertyString("controller").size() > 3)
                    {
                        InputManager* im = global.vgbLuaNamespace["controller"].cast <InputManager*> ();
                        im->addController(wrap, object.GetPropertyString("controller"));
                    }
                }
            }
        }
    }

    tmx::MapLoader* getTileMap() const
    {
        return m_tileMap;
    }

    void m_addComplexDynamicBody(tmx::MapObject& object, b2World* world, PhysicsComponent::Handle phandle)
    {
        b2Body* body = tmx::BodyCreator::Add(object, *world, b2_dynamicBody);

        /*here init the body from lua file*/
        if (phandle->configTable["restitution"])
            body->GetFixtureList()->SetRestitution(phandle->configTable["restitution"].cast <float> ());
        /*end of init*/

        if (phandle->body)
            world->DestroyBody(phandle->body);

        phandle->body = body;
    }

    void m_addComplexStaticBody(tmx::MapObject& object, b2World* world, PhysicsComponent::Handle phandle, entityx::Entity ent)
    {
        b2Body* body = tmx::BodyCreator::Add(object, *world);

        /*here init the body from lua file*/
        if (phandle->configTable["restitution"])
            body->GetFixtureList()->SetRestitution(phandle->configTable["restitution"].cast <float> ());
        /*end of init*/

        if (phandle->body)
            world->DestroyBody(phandle->body);

        phandle->body = body;

        GraphicsComponent::Handle ghandle = ent.component <GraphicsComponent> ();
        if (ghandle)
        {
            ghandle->sprite.setRotation(thor::toDegree(body->GetAngle()));
            ghandle->sprite.setPosition(si::pixels(body->GetPosition()));
        }
    }

private:
    void m_addComplexDynamicBody();
    void m_addComplexStaticBody();
    //void m_addSimpleStaticBody();

    tmx::MapLoader* m_tileMap;
};

#endif