#ifndef RENDERSYSTEM_HPP
#define RENDERSYSTEM_HPP

#include <SFML/Graphics/RenderTarget.hpp>
#include <entityx/entityx.h>

class RenderSystem : public entityx::System <RenderSystem>
{
public:
    explicit RenderSystem(sf::RenderTarget& target);
    void update(entityx::EntityManager &es, entityx::EventManager &events, entityx::TimeDelta dt);

private:
    sf::RenderTarget& m_renderTarget;
};

#endif