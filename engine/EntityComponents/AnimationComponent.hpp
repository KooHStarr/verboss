#ifndef ANIMATIONCOMPONENT_HPP
#define ANIMATIONCOMPONENT_HPP

#include <entityx/entityx.h>
#include <Thor/Animation.hpp>
#include "../Globals.hpp"

struct AnimationComponent : entityx::Component <AnimationComponent>
{
    AnimationComponent() : firstAnimationProcessLaunch (true) {}

    typedef thor::Animator <sf::Sprite, std::string> Animator;
    Animator animator;
    bool firstAnimationProcessLaunch;
};

#endif