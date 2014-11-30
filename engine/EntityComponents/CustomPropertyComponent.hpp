#ifndef CUSTOMPROPERTYCOMPONENT_HPP
#define CUSTOMPROPERTYCOMPONENT_HPP

#include <entityx/entityx.h>
#include <unordered_map>

struct CustomPropertyComponent : entityx::Component <CustomPropertyComponent>
{
    std::unordered_map <std::string, std::string> property;
};

#endif