#include "AnimationSystem.hpp"
#include "b2Converts.hpp"

void AnimationSystem::update(entityx::EntityManager &es, entityx::EventManager &events, entityx::TimeDelta dt)
{
    GraphicsComponent::Handle ghandle;
    AnimationComponent::Handle ahandle;

    for (auto entity : es.entities_with_components(ahandle, ghandle))
    {
        ahandle->animator.update(sf::seconds(dt));
        ahandle->animator.animate(ghandle->sprite);

        if (ahandle->firstAnimationProcessLaunch)
        {
            ahandle->firstAnimationProcessLaunch = false;
            sf::IntRect textureRect = ghandle->sprite.getTextureRect();
            ghandle->sprite.setOrigin(textureRect.left + textureRect.width / 2, textureRect.top - textureRect.height / 2);
        }
    }
}
