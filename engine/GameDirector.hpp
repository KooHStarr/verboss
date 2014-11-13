#ifndef GAMEDIRECTOR_HPP
#define GAMEDIRECTOR_HPP

#include "Application.hpp"
#include "Debug.hpp"

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <TGUI/TGUI.hpp>

class GameDirector
{
friend class TGUI_GuiWrapper;

public:
    GameDirector();

    void           run();
    void DEBUGrun();

    void           setApp(Application& app);
    void           setScriptManager(ScriptManager& sm);
    void           setFileSystem(FileSystem& fs);

    void           timePerFrame(sf::Time t);
    sf::Time       timePerFrame() const;

    SceneManager&  scenes();
    void           outputError(const std::string& message);

public:
    /*THIS IS VERY UGLY HACK*/
    //Wrapper for tgui::Gui class cause it is non copyable
    struct TGUI_GuiWrapper
    {
        TGUI_GuiWrapper() : gui(new tgui::Gui(s_gameDirector->m_app->window()))
        {
            std::cout << "TGUI_GuiWrapper constrictor\n";
        }
        ~TGUI_GuiWrapper() { delete gui; std::cout << "<TGUI_GuiWrapper> destructor\n"; }

        static GameDirector* s_gameDirector;
        tgui::Gui* gui;
    };

private:
    void            m_bind2Lua();

    Application*    m_app;
    sf::Time        m_timePerFrame;
    ScriptManager*  m_scriptManager;
    FileSystem*     m_fileSystem;
};

#endif // GAMEDIRECTOR_HPP
