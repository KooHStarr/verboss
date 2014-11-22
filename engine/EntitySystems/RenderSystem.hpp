#ifndef RENDERSYSTEM_HPP
#define RENDERSYSTEM_HPP

#include <tmx/MapLoader.h>
#include <algorithm>
#include "../EntityComponents/GraphicsComponent.hpp"
#include "DebugRender.hpp"
#include "TileMapSystem.hpp"

class RenderSystem : public entityx::System <RenderSystem>, public entityx::Receiver <RenderSystem>, public BasicSystem
{
public:
    RenderSystem(sf::RenderTarget& target)  :
            m_renderTarget(target)
    {}

    void configure(entityx::EventManager &event_manager)
    {
        event_manager.subscribe <entityx::ComponentAddedEvent <GraphicsComponent>> (*this);
    }

    void update(entityx::EntityManager &es, entityx::EventManager &events, entityx::TimeDelta dt)
    {

    }


    void render()
    {

        m_renderTileMapWithEntities();
        /*m_debugRender();
         */
    }

    void debugRender(bool flag)
    {
        /*m_releaseBox2dDebugDraw();
        if (flag)
        {
            m_debugDraw = new sf::DebugDraw(m_renderTarget);
            m_debugDraw->SetFlags(b2Draw::e_shapeBit);
            ->SetDebugDraw(m_debugDraw);
        }*/
    }

    void receive(const entityx::ComponentAddedEvent <GraphicsComponent>& event)
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

private:
    void m_renderTileMapWithEntities()
    {
        auto tileMap = m_entityManager->systems.system <TileMapSystem> ()->getTileMap();

        if (tileMap)
        {
            int renderOrder = 0;
            auto& layers = tileMap->GetLayers();

            for (auto& layer : layers)
            {
                if (layer.type == tmx::ObjectGroup)
                {
                    for (auto& entity : m_renderableEntities)
                    {
                        GraphicsComponent::Handle gchandle = entity.component <GraphicsComponent> ();
                        if (gchandle->renderOrder == renderOrder)
                            m_renderTarget.draw(gchandle->sprite);
                    }
                } else {
                    m_renderTarget.draw(layer);
                }

                renderOrder++;
            }
        } else {
            for (auto& entity : m_renderableEntities)
            {
                GraphicsComponent::Handle gchandle = entity.component <GraphicsComponent> ();
                m_renderTarget.draw(gchandle->sprite);
            }
        }
    }

    void m_releaseBox2dDebugDraw()
    {
        /*if (m_debugDraw)
        {
            delete m_debugDraw;
            m_debugDraw = nullptr;
        }*/
    }

private:
    //TileMapSystem* m_tileMapSystem;
    sf::RenderTarget&             m_renderTarget;
    std::vector <entityx::Entity> m_renderableEntities;
};

#endif