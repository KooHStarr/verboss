#ifndef PHYSICSSYSTEM_HPP
#define PHYSICSSYSTEM_HPP

#include <Thor/Math.hpp>
#include "EntityComponents/PhysicsComponent.hpp"
#include "EntityComponents/GraphicsComponent.hpp"
#include "BasicSystem.hpp"
#include "EntityWrapper.hpp"
#include "b2Converts.hpp"

class PhysicsSystem : public entityx::System <PhysicsSystem>, public BasicSystem
{
public:
    PhysicsSystem();
    ~PhysicsSystem();

    void update(entityx::EntityManager &es, entityx::EventManager &events, entityx::TimeDelta dt);
    void setWorld(b2World* world);
    b2World* getWorld() const;

    b2World* createWorld(float gravx, float gravy);

private:
    b2World* m_world;
};

#endif