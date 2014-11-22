#include "Globals.hpp"

PrivateGlobal global;

PrivateGlobal::PrivateGlobal() :
    vgbLuaNamespace(scriptManager.getGlobal("vgb"))
{}

PrivateGlobal::~PrivateGlobal()
{}