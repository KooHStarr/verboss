#ifndef APPLICATIONREG_HPP
#define APPLICATIONREG_HPP

#include "EntityFactory.hpp"

namespace bind2lua
{
    ///////////////////////////////////////////////
    inline void tileMapSystem(entityx::EntityX* ent)
    {
        global.scriptManager.globalNamespace()
                .beginNamespace("vgb")
                .beginClass <TileMapSystem> ("TileMapSystem")
                .addProperty("tileMap", &TileMapSystem::getTileMap, &TileMapSystem::setTileMap)
                .endClass()

                .beginClass <tmx::MapLoader> ("MapLoader")
                .endClass()
                .endNamespace();

        TileMapSystem* sys = ent->systems.system <TileMapSystem> ().get();
        global.vgbLuaNamespace["tileMapSystem"] = sys;
    }

    ////////////////////////////////////////////////
    inline void physicsSystem(entityx::EntityX* ent)
    {
        global.scriptManager.globalNamespace()
                .beginNamespace("vgb")
                .beginClass <PhysicsSystem> ("PhysicsSystem")
                .addProperty("world", &PhysicsSystem::getWorld, &PhysicsSystem::setWorld)
                .endClass()

                .beginClass <b2World> ("b2World")
                .endClass()
                .endNamespace();

        PhysicsSystem* sys = ent->systems.system <PhysicsSystem> ().get();
        global.vgbLuaNamespace["physicsSystem"] = sys;
    }

    /////////////////////////////////////////
    inline void application(Application *app)
    {
        global.scriptManager.globalNamespace()
                .beginNamespace("vgb")
                .beginClass <entityx::EntityManager>("EntityManager")
                .addFunction("create", &entityx::EntityManager::create)
                .endClass()

                .addFunction("createEntity",  &bind2lua::createEntity)
                .addFunction("createEntityF", &bind2lua::createEntityF)
                .endNamespace();

        bind2lua::app = app;
        tileMapSystem(app);
        physicsSystem(app);
    }
}

#endif