#ifndef ANIMATIONSYSTEM_HPP
#define ANIMATIONSYSTEM_HPP

#include <entityx/entityx.h>

#include "Globals.hpp"
#include "BasicSystem.hpp"
#include "EntityWrapper.hpp"
#include "EntityComponents/CustomPropertyComponent.hpp"
#include "EntityManagerWrapper.hpp"
#include "PhysicsSystem.hpp"


class AnimationSystem : public entityx::System <AnimationSystem>, public BasicSystem
{
public:
    void update(entityx::EntityManager &es, entityx::EventManager &events, entityx::TimeDelta dt);

private:

};

#endif