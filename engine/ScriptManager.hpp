#ifndef SCRIPTMANAGER_HPP
#define SCRIPTMANAGER_HPP

#include "Exception.hpp"

#include <fstream>
#include <lua.hpp>

class ScriptManager
{
public:
    ScriptManager();
    ~ScriptManager();

    void                  doString(const std::string& script);
    void                  doFile  (const std::string& file);
    lua_State*            getVM()  const;
    //luabridge::Namespace& globalNamespace();


private:
    lua_State* L;
};

#endif // SCRIPTMANAGER_HPP
