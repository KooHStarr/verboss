#ifndef EXCEPTION_HPP
#define EXCEPTION_HPP

#include <sstream>
#include <string>
#include <lua.hpp>
#include <LuaBridge.h>

class Exception
{
public:
    Exception(const std::string& info, const std::string& message) :
              m_info(info),
              m_what(message)
    {}

    Exception(const std::string& info, lua_State* l) :
            m_info(info),
            L(l)
    {
        m_what += lua_tostring(L, -1);
        m_what += "\nStack traceback >>\n";
        luabridge::LuaRef d = luabridge::getGlobal(L, "debug");
        m_what += d["traceback"]().tostring();
    }

    const std::string& info() const
    {
        return m_info;
    }

    const std::string& what() const
    {
        return m_what;
    }


private:
    std::string m_info;
    std::string m_what;
    lua_State*  L;
};

#endif // EXCEPTION_HPP
