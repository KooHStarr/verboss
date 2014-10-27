#include "Application.hpp"
#include <TGUI/Gui.hpp>

Application::Application() :
    m_window(sf::VideoMode(800, 600), "alpha"),
    m_console(m_window, *m_resourceManager.load <sf::Font> ("font", thor::Resources::fromFile <sf::Font> ("assets/font.ttf")), m_sceneManager.getScriptManager())
{

}

void Application::event()
{
    sf::Event event;

    while (m_window.pollEvent(event))
    {
        /*here check from lua variables*/
        if (event.type == sf::Event::Closed)
            m_window.close();

        ScriptManager* sm = m_sceneManager.getScriptManager();

        if (event.type == sf::Event::KeyPressed)
        {
            if (m_sceneManager.currentScene().name() == "TestScene")
                m_sceneManager.changeScene("TestScene2");
            else
                m_sceneManager.changeScene("TestScene");
        }

        //handle event for tgui::Gui class
        luabridge::LuaRef vgb = sm->getGlobal("vgb");
        if (!vgb["currentGui"].isNil())
        {
            //std::cout << "GUI Event\n";
            tgui::Gui* gui = vgb["currentGui"];
            gui->handleEvent(event);
        }

        m_console.handleEvent(event);
    }
}

void Application::update(sf::Time dt)
{
    m_sceneManager.currentScene().update(dt);
    m_console.update(dt);
    m_sceneManager.getScriptManager()->doString("collectgarbage() ");
}

void Application::render()
{
    m_window.clear();
    m_sceneManager.currentScene().render(m_window);
    m_console.render();
    m_window.display();
}

bool Application::isOpen() const
{
    return m_sceneManager.hasRunningScene() ? m_window.isOpen() : false;
}

SceneManager& Application::scenes()
{
    return m_sceneManager;
}

sf::RenderWindow& Application::window()
{
    return m_window;
}

ResourceManager& Application::resourceManager()
{
    return m_resourceManager;
}