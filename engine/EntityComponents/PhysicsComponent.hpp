#ifndef PHYSICSCOMPONENT_HPP
#define PHYSICSCOMPONENT_HPP

#include <entityx/entityx.h>
#include <Box2D/Box2D.h>

struct PhysicsComponent : entityx::Component <PhysicsComponent>
{
    PhysicsComponent() : body(nullptr), configTable(global.vgbLuaNamespace) {}
    b2Body* body;
    luabridge::LuaRef configTable;
};

#endif