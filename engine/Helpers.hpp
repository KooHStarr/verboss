#ifndef HELPERS_HPP
#define HELPERS_HPP

#include <vector>
#include "Globals.hpp"

void detail_addTableNameKey(const std::string& key);

class LuaTableIterator
{
    friend void detail_addTableNameKey(const std::string& key);

public:
    LuaTableIterator(const std::string& tablename);
    ~LuaTableIterator();

    static std::vector <std::string> keys;
};

#endif