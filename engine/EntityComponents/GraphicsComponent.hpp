#ifndef GRAPHICSCOMPONENT_HPP
#define GRAPHICSCOMPONENT_HPP

#include <entityx/entityx.h>

struct GraphicsComponent : entityx::Component <GraphicsComponent>
{
    int        renderOrder;
    sf::Sprite sprite;
};

#endif