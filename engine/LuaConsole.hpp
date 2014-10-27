#ifndef LUACONSOLE_HPP
#define LUACONSOLE_HPP

#include "ScriptManager.hpp"
#include <TGUI/TGUI.hpp>

class LuaConsole
{
public:
    LuaConsole(sf::RenderWindow& wnd, sf::Font& font, ScriptManager* sm);

    void handleEvent(sf::Event& event);
    void update(sf::Time dt);
    void render();

private:
    void m_toggleConsole();
    void m_handleCallbacks();

    tgui::ChatBox* m_chatBox;
    tgui::EditBox* m_editBox;
    tgui::Gui      m_gui;
    ScriptManager* m_scriptManager;
    bool           m_isActive;
};

#endif