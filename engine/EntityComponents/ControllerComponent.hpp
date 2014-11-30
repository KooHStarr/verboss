#ifndef CONTROLLERCOMPONENT_HPP
#define CONTROLLERCOMPONENT_HPP

#include <entityx/entityx.h>
#include "../Globals.hpp"

struct ControllerComponent : entityx::Component <ControllerComponent>
{
    ControllerComponent() : inputTable(global.vgbLuaNamespace) {}
    luabridge::LuaRef inputTable;
    std::string inputTableName;
};

#endif