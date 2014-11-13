#ifndef BODYCOMPONENT_HPP
#define BODYCOMPONENT_HPP

#include <entityx/entityx.h>
#include <Box2d/Box2d.h>

struct BodyComponent : entityx::Component <BodyComponent>
{
    b2Body* body;
};

#endif