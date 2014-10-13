#include "ScriptManager.hpp"

ScriptManager::ScriptManager() :
    L(nullptr)
{
    L = luaL_newstate();
    if(!L)
        throw Exception("[From C++] <ScriptManager::ScriptManager> Couldn't init lua, " + std::string(lua_tostring(L, -1)));

    luaL_openlibs(L);
    //luabind::open(L);

    //LuaErrorHandler::setLuaVM(L);
    //luabind::set_pcall_callback(&LuaErrorHandler::err);
}


ScriptManager::~ScriptManager()
{
    lua_close(L);
}

void ScriptManager::doString(const std::string& script)
{
    if(luaL_dostring(L, script.c_str()))
        throw Exception(std::string("[From C++] <ScriptManager::doString> Couldn't execute string: \n") + script + "\nReason:" +
                                lua_tostring(L, -1));
}

void ScriptManager::doFile(const std::string& filename)
{
    std::ifstream file(filename);
    std::string   data;

    if (!file.is_open() || !file.good())
        throw Exception("[From C++] <ScriptManager::doFile> Couldn't open script '" + filename + "'\n");

    while(!file.eof())
    {
        std::string temp;
        std::getline(file, temp);
        data += temp;
        data += "\n";
    }

    doString(data);
}

lua_State* ScriptManager::getVM() const
{
    return L;
}
/*luabridge::Namespace& ScriptManager::globalNamespace()
{
    return luabridge::getGlobalNamespace(L);
}*/