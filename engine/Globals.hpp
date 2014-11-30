#ifndef GLOBALS_HPP
#define GLOBALS_HPP

#include "ScriptManager.hpp"
#include "StdCapture.hpp"

struct PrivateGlobal
{
    PrivateGlobal();
    ~PrivateGlobal();

    ScriptManager     scriptManager;
    luabridge::LuaRef vgbLuaNamespace;
    StdCapture        stdCapture;
};

extern PrivateGlobal global;

#endif