#include "../EntityWrapper.hpp"
#ifndef PHYSICSCOMPONENT_HPP
#define PHYSICSCOMPONENT_HPP

#include <entityx/entityx.h>
#include <Box2D/Box2D.h>
#include "../Globals.hpp"

class EntityWrapper;

struct PhysicsComponent : entityx::Component <PhysicsComponent>
{
    PhysicsComponent() : body(nullptr), configTable(global.vgbLuaNamespace) {}
    ~PhysicsComponent()
    {
        //EntityWrapper* wrap = static_cast <EntityWrapper*> (body->GetUserData());
        //delete wrap;
        //body->GetWorld()->DestroyBody(body);
        //body = nullptr;
    }

    b2Body* body;
    luabridge::LuaRef configTable;
};

#endif