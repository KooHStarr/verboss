#ifndef FILESYSTEM_HPP
#define FILESYSTEM_HPP

#include "FileStream.hpp"
#include <TGUI/TGUI.hpp>

class FileSystem
{
public:
    FileSystem(const char* argv0);
    ~FileSystem();

    void addSearchPath(const std::string& path, bool append = true);
    void setGuiResourcePath(const std::string& path);
    bool existsFile(const std::string& filename);
};

#endif