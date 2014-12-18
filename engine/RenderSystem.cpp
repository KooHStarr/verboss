#include "RenderSystem.hpp"

///////////////////////////////////////////////////////
RenderSystem::RenderSystem(sf::RenderTarget& target)  :
    m_renderTarget(target),
    m_debugDraw(nullptr),
    m_showFPS(false),
    m_updateTime(0),
    m_numFrames(0) {}


/////////////////////////////
RenderSystem::~RenderSystem()
{
    m_releaseBox2dDebugDraw();
}


/////////////////////////////////////////////////////
void RenderSystem::configure(entityx::EventManager &event_manager)
{
    event_manager.subscribe <entityx::ComponentAddedEvent <GraphicsComponent>> (*this);
}


/////////////////////////////////////////////////////////////////////////////////////////////
void RenderSystem::update(entityx::EntityManager &es, entityx::EventManager &events, entityx::TimeDelta dt)
{
    m_dt = dt;
}


//////////////////////////
void RenderSystem::render()
{
    if (m_showFPS)
        m_calculateFPS(m_dt);

    m_renderTileMapWithEntities();
    m_debugRender();
}


/////////////////////////////////////////
void RenderSystem::debugRender(bool flag)
{
    m_releaseBox2dDebugDraw();
    if (flag)
    {
        m_debugDraw = new sf::DebugDraw(m_renderTarget);
        m_debugDraw->SetFlags(b2Draw::e_shapeBit);
        m_entityManager->systems.system <PhysicsSystem> ()->getWorld()->SetDebugDraw(m_debugDraw);
    }
}


/////////////////////////////////////////////////////////////////////////////////////////
void RenderSystem::receive(const entityx::ComponentAddedEvent <GraphicsComponent>& event)
{
    entityx::Entity ent = event.entity;
    m_renderableEntities.push_back(event.entity);

    std::sort(m_renderableEntities.begin(), m_renderableEntities.end(), [] (entityx::Entity a, entityx::Entity b)
    {
        GraphicsComponent::Handle ah = a.component <GraphicsComponent> ();
        GraphicsComponent::Handle bh = b.component <GraphicsComponent> ();
        return ah->renderOrder < bh->renderOrder;
    });
}


//////////////////////////////////////
void RenderSystem::showFPS(bool flag)
{
    m_showFPS = flag;

    if (flag)
    {
        ResourceManager* rm = global.vgbLuaNamespace["resourceManager"];
        m_fpsText.setFont(*rm->get <sf::Font> ("default"));
        m_fpsText.setCharacterSize(12);
        m_fpsText.setColor(sf::Color::White);
    }
}


////////////////////////////////////////////////
void RenderSystem::m_renderTileMapWithEntities()
{
    auto tileMap = m_entityManager->systems.system <TileMapSystem> ()->getTileMap();

    if (tileMap)
    {
        int layerCount = 0;
        auto& layers = tileMap->GetLayers();

        for (auto& layer : layers)
        {
            layerCount++;

            if (layer.type == tmx::ObjectGroup)
            {
                for (auto& entity : m_renderableEntities)
                {
                    GraphicsComponent::Handle gchandle = entity.component <GraphicsComponent> ();
                    if (gchandle->renderOrder == layerCount)
                        m_renderTarget.draw(gchandle->sprite);
                }
            } else {
                m_renderTarget.draw(layer);
            }
        }
    } else {
        for (auto& entity : m_renderableEntities)
        {
            GraphicsComponent::Handle gchandle = entity.component <GraphicsComponent> ();
            m_renderTarget.draw(gchandle->sprite);
        }
    }
}


/////////////////////////////////////////////
void RenderSystem::m_releaseBox2dDebugDraw()
{
    if (m_debugDraw)
    {
        delete m_debugDraw;
        m_debugDraw = nullptr;
    }
}


/////////////////////////////////
void RenderSystem::m_debugRender()
{
    if (m_debugDraw)
        m_entityManager->systems.system <PhysicsSystem> ()->getWorld()->DrawDebugData();

    if (m_showFPS)
        m_renderTarget.draw(m_fpsText);
}


////////////////////////////////////////////////////////
void RenderSystem::m_calculateFPS(entityx::TimeDelta dt)
{
    m_updateTime += dt;
    m_numFrames += 1;

    if (m_updateTime >= 1.0f)
    {
        std::stringstream ss;
        ss << "FPS: " << m_numFrames;
        m_fpsText.setString(ss.str());
        m_updateTime -= 1.0f;
        m_numFrames = 0;
    }
}