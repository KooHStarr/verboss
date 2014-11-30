#ifndef PHYSICSSYSTEM_HPP
#define PHYSICSSYSTEM_HPP

#include <Thor/Math.hpp>
#include "../EntityComponents/PhysicsComponent.hpp"
#include "BasicSystem.hpp"
#include "../b2Converts.hpp"

class PhysicsSystem : public entityx::System <PhysicsSystem>, public BasicSystem
{
public:
    PhysicsSystem() : m_world(nullptr)
    {}

    void update(entityx::EntityManager &es, entityx::EventManager &events, entityx::TimeDelta dt)
    {
        getWorld()->Step(dt, 8, 6);

        PhysicsComponent::Handle  phandle;
        GraphicsComponent::Handle ghandle;

        for (auto entity : es.entities_with_components(phandle, ghandle))
        {
            if (phandle->body->GetType() == b2_dynamicBody)
            {
                ghandle->sprite.setRotation(thor::toDegree(phandle->body->GetAngle()));
                ghandle->sprite.setPosition(si::pixels(phandle->body->GetPosition()));
            }
        }
    }

    void setWorld(b2World* world)
    {
        m_world = world;
    }

    b2World* getWorld() const
    {
        if (!m_world)
            throw Exception("<PhysicsSystem::getWorld>", "Attempt to return an invalid world.\n");

        return m_world;
    }

private:
    b2World* m_world;
};

#endif