#include "Helpers.hpp"

std::vector <std::string> LuaTableIterator::keys;

///////////////////////////////////////////////////////////////
LuaTableIterator::LuaTableIterator(const std::string& tablename)
{
    std::string temp = "function detail_hackFunc() for k, _ in pairs(" + tablename + ") do vgb.detail_addTableNameKey(k) end end\n"
            "detail_hackFunc()\n detail_hackFunc = nil\n";
    global.scriptManager.doString(temp);
}


////////////////////////////////////////
LuaTableIterator::~LuaTableIterator()
{
    keys.clear();
}


///////////////////////////////////////////////////
void detail_addTableNameKey(const std::string& key)
{
    LuaTableIterator::keys.push_back (key);
}