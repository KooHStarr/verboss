#ifndef GLOBALS_HPP
#define GLOBALS_HPP

#include "ScriptManager.hpp"

struct PrivateGlobal
{
    PrivateGlobal();
    ~PrivateGlobal();

    ScriptManager     scriptManager;
    luabridge::LuaRef vgbLuaNamespace;
};

extern PrivateGlobal global;

#endif