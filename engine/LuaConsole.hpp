#include "Application.hpp"
#ifndef LUACONSOLE_HPP
#define LUACONSOLE_HPP

#include "Globals.hpp"
#include <TGUI/TGUI.hpp>

class Application;

class LuaConsole
{
public:
    LuaConsole(Application* app, sf::Font& font);

    void handleEvent(sf::Event& event);
    void update(sf::Time dt);
    void render();

private:
    void m_toggleConsole();
    void m_handleCallbacks();
    void m_checkCommand(const std::string& command);

    Application*   m_app;
    tgui::ChatBox* m_chatBox;
    tgui::EditBox* m_editBox;
    tgui::Gui      m_gui;
    bool           m_isActive;
    std::string    m_captured;
};

#endif