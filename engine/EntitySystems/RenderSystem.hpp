#ifndef RENDERSYSTEM_HPP
#define RENDERSYSTEM_HPP

#include <SFML/Graphics/RenderTarget.hpp>
#include "../EntityComponents/GraphicsComponent.hpp"

class RenderSystem : public entityx::System <RenderSystem>
{
public:
    RenderSystem(sf::RenderTarget& target)  :
            m_renderTarget(target)
    {}
    void update(entityx::EntityManager &es, entityx::EventManager &events, entityx::TimeDelta dt)
    {
        //std::cout << "updating render system with dt = " << dt << "\n";
        //for (ex::Entity entity : es.entities_with_components(renderable))
        //draw object
    }

    void render(entityx::EntityManager &es)
    {
        GraphicsComponent::Handle gc;

        for (entityx::Entity entity : es.entities_with_components(gc))
        {
            m_renderTarget.draw(gc->sprite);
        }
    }

private:
    sf::RenderTarget& m_renderTarget;
};

#endif