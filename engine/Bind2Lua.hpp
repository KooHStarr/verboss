#ifndef BIND2LUA_HPP
#define BIND2LUA_HPP

namespace bind2lua
{
    namespace detail
    {
        ScriptManager*   sm;
        ResourceManager* rm;

        inline void regGui()
        {
            sm->globalNamespace()
                    .beginNamespace("vgb")
                        .beginClass <tgui::Gui> ("tguiGui")
                            .addFunction("loadWidgetsFromFile", &tgui::Gui::loadWidgetsFromFile)
                            .addFunction("render", &tgui::Gui::draw)
                            .addFunction("setGlobalFont", (bool (tgui::Gui::*) (const std::string&)) &tgui::Gui::setGlobalFont)
                        .endClass()
                    .endNamespace();
        }
    }

    inline void scriptManager(ScriptManager* sm)
    {
        detail::sm = sm;

        detail::sm->globalNamespace()
                .beginNamespace("vgb")
                    .beginClass <ScriptManager> ("ScriptManager")
                        .addFunction("import", &ScriptManager::doFile)
                    .endClass()
                .endNamespace();

        luabridge::LuaRef t = detail::sm->getGlobal("vgb");
        t["detail_scriptManager"] = sm;
        detail::sm->doString("function import(filename) vgb.detail_scriptManager:import(filename) end\n");
    }

    inline void gameDirector(GameDirector* dir)
    {
        detail::sm->globalNamespace()
                .beginNamespace("vgb")
                    .beginClass <GameDirector> ("GameDirector")
                        .addFunction("scenes", &GameDirector::scenes)
                    .endClass()
                .endNamespace();

        luabridge::LuaRef t = detail::sm->getGlobal("vgb");
        t["director"] = dir;
    }

    inline void sceneManager()
    {
        detail::sm->globalNamespace()
                .beginNamespace("vgb")
                    .beginClass <SceneManager> ("SceneManager")
                        .addFunction("addScene", &SceneManager::addScene)
                        .addFunction("changeScene", &SceneManager::changeScene)
                    .endClass()
                .endNamespace();
    }

    inline void fileSystem(FileSystem* fs)
    {
        detail::sm->globalNamespace()
                .beginNamespace("vgb")
                    .beginClass <FileSystem> ("FileSystem")
                        .addFunction("addSearchPath", &FileSystem::addSearchPath)
                    .endClass()
                .endNamespace();

        luabridge::LuaRef t = detail::sm->getGlobal("vgb");
        t["fileSystem"] = fs;
    }

    inline void gui()
    {
        detail::sm->globalNamespace()
                .beginNamespace("vgb")
                    .beginClass <GameDirector::TGUI_GuiWrapper> ("TGUI_GuiWrapper")
                        .addConstructor <void (*) (void)> ()
                        .addData("gui", &GameDirector::TGUI_GuiWrapper::gui)
                    .endClass()
                .endNamespace();

        detail::regGui();

        detail::sm->doString("function vgb.Gui()\n"
                             "vgb.detail_gui_wrapper = vgb.TGUI_GuiWrapper()\n"
                             "vgb.currentGui = vgb.detail_gui_wrapper.gui\n"
                             "return vgb.currentGui\n end\n");
    }

    inline void resourceManager(ResourceManager* rm)
    {
        detail::rm = rm;

        detail::sm->globalNamespace()
                .beginNamespace("vgb")
                .endNamespace();

        luabridge::LuaRef t  = detail::sm->getGlobal("vgb");
        t["resourceManager"] = rm;
    }
}

#endif