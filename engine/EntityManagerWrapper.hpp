#ifndef ENTITYMANAGERWRAPPER_HPP
#define ENTITYMANAGERWRAPPER_HPP

#include "EntityWrapper.hpp"
#include "EntityComponents/CustomPropertyComponent.hpp"
#include "EntityComponents/GraphicsComponent.hpp"
#include "ResourceManager.hpp"

class EntityManagerWrapper
{
public:
    EntityWrapper getEntityByName(const std::string& name);
    void setManager(entityx::EntityX* manager);
    EntityWrapper createEntity();
    EntityWrapper createEntityF(const std::string& entity_name);

private:
    void m_addGraphicsComponent(entityx::Entity entity, luabridge::LuaRef gchandle);
    void m_addPhysicsComponent (entityx::Entity entity, luabridge::LuaRef phandle);

    entityx::EntityX* m_manager;
};

#endif