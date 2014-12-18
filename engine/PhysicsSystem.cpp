#include "PhysicsSystem.hpp"

//////////////////////////////////
PhysicsSystem::PhysicsSystem() : m_world(nullptr)
{}


///////////////////////////////
PhysicsSystem::~PhysicsSystem()
{
    if (m_world)
    {
        delete m_world;
        m_world = nullptr;
    }
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PhysicsSystem::update(entityx::EntityManager &es, entityx::EventManager &events, entityx::TimeDelta dt)
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


///////////////////////////////////////////
void PhysicsSystem::setWorld(b2World* world)
{
    m_world = world;
}


////////////////////////////////////////
b2World* PhysicsSystem::getWorld() const
{
    if (!m_world)
        throw Exception("<PhysicsSystem::getWorld>", "Attempt to return an invalid world.\n");

    return m_world;
}


/////////////////////////////////////////////////////////////
b2World* PhysicsSystem::createWorld(float gravx, float gravy)
{
    m_world = new b2World(b2Vec2(gravx, gravy));
    return getWorld();
}