#ifndef PHYSICSCOMPONENT_HPP
#define PHYSICSCOMPONENT_HPP

#include <entityx/entityx.h>
#include <Box2D/Box2D.h>
#include "../Globals.hpp"

struct PhysicsComponent : entityx::Component <PhysicsComponent>
{
    PhysicsComponent() : body(nullptr), configTable(global.vgbLuaNamespace) {}
    ~PhysicsComponent()
    {
        //body->GetWorld()->DestroyBody(body);
        //body = nullptr;
    }

    b2Body* body;
    luabridge::LuaRef configTable;
};

#endif