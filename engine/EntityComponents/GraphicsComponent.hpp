#ifndef GRAPHICSCOMPONENT_HPP
#define GRAPHICSCOMPONENT_HPP

#include <entityx/entityx.h>
#include <SFML/Graphics/Sprite.hpp>

struct GraphicsComponent : entityx::Component <GraphicsComponent>
{
    sf::Sprite sprite;
};

#endif