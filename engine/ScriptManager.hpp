#ifndef SCRIPTMANAGER_HPP
#define SCRIPTMANAGER_HPP

#include "Exception.hpp"
#include "FileSystem.hpp"

#include <fstream>
#include <lua.hpp>
#include <LuaBridge.h>

class ScriptManager
{
public:
    ScriptManager();
    ~ScriptManager();

    void                  doString(const std::string& script);
    void                  doFile  (const std::string& file);

    luabridge::Namespace globalNamespace();
    luabridge::LuaRef    getGlobal(const std::string &var_name);

private:
    lua_State* L;
};

#endif // SCRIPTMANAGER_HPP
