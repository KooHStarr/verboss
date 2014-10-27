#include "ScriptManager.hpp"

ScriptManager::ScriptManager() :
    L(nullptr)
{
    L = luaL_newstate();
    assert(L);

    luaL_openlibs(L);
    doString("vgb = {} "
             "collectgarbage('stop') ");
}


ScriptManager::~ScriptManager()
{
    lua_close(L);
}

void ScriptManager::doString(const std::string& script)
{
    if(luaL_dostring(L, script.c_str()))
        throw Exception("<ScriptManager::doString>", lua_tostring(L, -1));
}

void ScriptManager::doFile(const std::string& filename)
{
    FileStream file(filename);

    if (!file.isOpen())
        throw Exception("<ScriptManager::doFile>", "Couldn't open script '" + filename + "'\n");

    std::string data = file.content();
    doString(data);
}

luabridge::Namespace ScriptManager::globalNamespace()
{
    return luabridge::getGlobalNamespace(L);
}

luabridge::LuaRef ScriptManager::getGlobal(const std::string &var_name)
{
    return luabridge::getGlobal(L, var_name.c_str());
}
