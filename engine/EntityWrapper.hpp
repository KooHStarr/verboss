#ifndef ENTITYWRAPPER_HPP
#define ENTITYWRAPPER_HPP

#include <entityx/entityx.h>
#include <CustomPropertyComponent.hpp>
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

    void addProperty(const std::string& key, const std::string& val)
    {
        CustomPropertyComponent::Handle cphandle = m_entity.component <CustomPropertyComponent> ();
        cphandle->property[key] = val;
    }

    std::string getProperty(const std::string& key)
    {
        CustomPropertyComponent::Handle cphandle = m_entity.component <CustomPropertyComponent> ();
        return cphandle->property[key];
    }

private:
    entityx::Entity m_entity;
};

#endif