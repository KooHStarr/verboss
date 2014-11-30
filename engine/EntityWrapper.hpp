#ifndef ENTITYWRAPPER_HPP
#define ENTITYWRAPPER_HPP

#include <entityx/entityx.h>
#include "EntityComponents/PhysicsComponent.hpp"

class EntityWrapper
{
public:
    EntityWrapper() {}
    EntityWrapper(entityx::Entity ent) : m_entity(ent) {}
    EntityWrapper(const EntityWrapper& e) : m_entity(e.m_entity) {}

    b2Body* getBody() const
    {
        entityx::Entity entity = m_entity;
        PhysicsComponent::Handle phandle = entity.component <PhysicsComponent> ();
        return phandle->body;
    }

    entityx::Entity getEntity()
    {
        return m_entity;
    }

private:
    entityx::Entity m_entity;
};

#endif