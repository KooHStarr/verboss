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
        throw Exception("<ScriptManager::doString>", L);
}

void ScriptManager::doFile(const std::string& filename)
{
    std::ifstream file(filename);
    std::string data;

    if(!file.is_open() || !file.good())
        throw Exception("SHEAT", filename);

    while(!file.eof())
    {
        std::string temp;
        std::getline(file, temp);
        data += temp;
        data += "\n";
    }

    doString(data);
    /*FileStream file(filename);

    if (!file.isOpen())
        throw Exception("<ScriptManager::doFile>", "Couldn't open script '" + filename + "'\n");

    std::string data = file.content();
    std::cout << "Doing file '" << filename << "'\n";
    doString(data);*/
}

luabridge::Namespace ScriptManager::globalNamespace()
{
    return luabridge::getGlobalNamespace(L);
}

luabridge::LuaRef ScriptManager::getGlobal(const std::string &var_name)
{
    return luabridge::getGlobal(L, var_name.c_str());
}
