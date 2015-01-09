#ifndef DEBUG_HPP
#define DEBUG_HPP

#include <iostream>
#include <conio.h>

namespace debug
{
    inline void stop()
    {
        getch();
    }

    inline void print(const std::string& name)
    {
        printf ("%s\n", name.c_str());
    }
}

#endif