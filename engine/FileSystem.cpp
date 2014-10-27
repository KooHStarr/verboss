#include "FileSystem.hpp"

FileSystem::FileSystem(const char* argv0)
{
    PHYSFS_init(argv0);
    std::string basePath = argv0;

    auto pos = basePath.find_last_of(PHYSFS_getDirSeparator(), basePath.length());
    if (pos != std::string::npos)
        basePath.erase(pos);

    addSearchPath(basePath, false);
}

FileSystem::~FileSystem()
{
    PHYSFS_deinit();
}

void FileSystem::addSearchPath(const std::string &path, bool append)
{
    PHYSFS_addToSearchPath(path.c_str(), append);
}

void FileSystem::setGuiResourcePath(const std::string& path)
{
    tgui::setResourcePath(path);
}

bool FileSystem::existsFile(const std::string& filename)
{
    return PHYSFS_exists(filename.c_str());
}