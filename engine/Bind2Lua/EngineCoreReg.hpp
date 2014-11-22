#ifndef ENGINECOREREG_HPP
#define ENGINECOREREG_HPP

#include "../Globals.hpp"

namespace bind2lua
{
    inline void import(const char* filename)
    {
        global.scriptManager.doFile(filename);
    }

    inline void core()
    {
        global.scriptManager.globalNamespace()
                .beginNamespace("vgb")
                .addFunction("import", &import)
                .endNamespace();
    }

    //////////////////////////////////////////
    inline void gameDirector(GameDirector* dir)
    {
        global.scriptManager.globalNamespace()
                .beginNamespace("vgb")
                .beginClass <GameDirector> ("GameDirector")
                .addFunction("scenes", &GameDirector::scenes)
                .endClass()
                .endNamespace();

        global.vgbLuaNamespace["director"] = dir;
    }


    //////////////////////////
    inline void sceneManager()
    {
        global.scriptManager.globalNamespace()
                .beginNamespace("vgb")
                .beginClass <SceneManager> ("SceneManager")
                .addFunction("addScene", &SceneManager::addScene)
                .addFunction("changeScene", &SceneManager::changeScene)
                .addFunction("removeScene", &SceneManager::removeScene)
                .endClass()
                .endNamespace();
    }


    //////////////////////////////////////
    inline void fileSystem(FileSystem* fs)
    {
        global.scriptManager.globalNamespace()
                .beginNamespace("vgb")
                .beginClass <FileSystem> ("FileSystem")
                .addFunction("addSearchPath", &FileSystem::addSearchPath)
                .endClass()
                .endNamespace();

        global.vgbLuaNamespace["fileSystem"] = fs;
    }


    ////////////////////////////////////////////////
    inline void resourceManager(ResourceManager* rm)
    {
        global.scriptManager.globalNamespace()
                .beginNamespace("vgb")
                .beginClass <ResourceManager> ("ResourceManager")
                .addFunction("loadTileMap", &ResourceManager::loadTileMap)
                .addFunction("createWorld", &ResourceManager::createWorld)
                .endClass()
                .endNamespace();

        global.vgbLuaNamespace["resourceManager"] = rm;
    }

}

#endif