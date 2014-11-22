#ifndef PHYSICSSYSTEM_HPP
#define PHYSICSSSYTEM_HPP

#include "../EntityComponents/PhysicsComponent.hpp"
#include "BasicSystem.hpp"

class PhysicsSystem : public entityx::System <PhysicsSystem>, public BasicSystem
{
public:
    PhysicsSystem() : m_world(nullptr)
    {}

    void update(entityx::EntityManager &es, entityx::EventManager &events, entityx::TimeDelta dt)
    {

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