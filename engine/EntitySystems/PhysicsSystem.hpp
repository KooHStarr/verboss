#ifndef PHYSICSSYSTEM_HPP
#define PHYSICSSYSTEM_HPP

#include "../EntityComponents/BodyComponent.hpp"
#include "DebugRender.hpp"

class PhysicsSystem : public entityx::System <PhysicsSystem>
{
public:
    PhysicsSystem(sf::RenderTarget& target) :
            m_world(nullptr),
            m_rubeWorld(false),
            m_velocityIterations(8),
            m_positionIterations(5),
            m_renderTarget(target),
            m_debugDraw(nullptr)
    {}

    ~PhysicsSystem()
    {
        destroy();
        m_releaseDebugDraw();
    }

    void create(int xgrav, int ygrav)
    {
        m_world = new b2World(b2Vec2(xgrav, ygrav));
    }

    void destroy()
    {
        if (!m_rubeWorld && m_world)
        {
            delete m_world;
            m_world = nullptr;
        }
    }

    void update(entityx::EntityManager &es, entityx::EventManager &events, entityx::TimeDelta dt)
    {
        std::cout << "updating physics system with dt = " << dt << "\n";
        assert(m_world && "<PhysicsSystem::update> m_world is nullptr!");
        m_world->Step(dt, m_velocityIterations, m_positionIterations);
    }

    void render()
    {
        if (m_debugDraw)
            m_world->DrawDebugData();
    }

    void setWorld(b2World* world)
    {
        m_world = world;
    }

    b2World* getWorld()
    {
        assert(m_world && "<PhysicsSystem::getWorld> m_world is nullptr!");
        return m_world;
    }

    void debugRender(bool flag)
    {
        m_releaseDebugDraw();
        if (flag)
        {
            m_debugDraw = new sf::DebugDraw(m_renderTarget);
            m_debugDraw->SetFlags(b2Draw::e_shapeBit);
            m_world->SetDebugDraw(m_debugDraw);
        }
    }

private:
    void m_releaseDebugDraw()
    {
        if (m_debugDraw)
        {
            delete m_debugDraw;
            m_debugDraw = nullptr;
        }
    }

private:
    //void m_createDebugDraw();

    b2World*          m_world;
    bool              m_rubeWorld;
    int32             m_velocityIterations;
    int32             m_positionIterations;

    sf::RenderTarget& m_renderTarget;
    sf::DebugDraw*    m_debugDraw;
};

#endif