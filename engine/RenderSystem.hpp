#ifndef RENDERSYSTEM_HPP
#define RENDERSYSTEM_HPP

#include <tmx/MapLoader.h>
#include <algorithm>
#include "EntityComponents/GraphicsComponent.hpp"
#include "DebugRender.hpp"
#include "TileMapSystem.hpp"
#include "ResourceManager.hpp"

class RenderSystem : public entityx::System <RenderSystem>, public entityx::Receiver <RenderSystem>, public BasicSystem
{
public:
    RenderSystem(sf::RenderTarget& target);
    ~RenderSystem();
    void configure(entityx::EventManager &event_manager);
    void update(entityx::EntityManager &es, entityx::EventManager &events, entityx::TimeDelta dt);
    void render();
    void debugRender(bool flag);
    void receive(const entityx::ComponentAddedEvent <GraphicsComponent>& event);
    void showFPS(bool flag);

private:
    void m_renderTileMapWithEntities();
    void m_releaseBox2dDebugDraw();
    void m_debugRender();
    void m_calculateFPS(entityx::TimeDelta dt);

private:
    sf::RenderTarget&             m_renderTarget;
    std::vector <entityx::Entity> m_renderableEntities;
    sf::DebugDraw*                m_debugDraw;

    bool                          m_showFPS;
    sf::Text                      m_fpsText;
    entityx::TimeDelta            m_updateTime;
    int                           m_numFrames;
    entityx::TimeDelta            m_dt;
};

#endif