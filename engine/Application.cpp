#include "Application.hpp"
#include <TGUI/Gui.hpp>

Application::Application(ScriptManager* sm) :
    m_window(sf::VideoMode(800, 600), "alpha"),
    m_console(m_window, *m_resourceManager.load <sf::Font> ("main_font", thor::Resources::fromFile <sf::Font> ("assets/font.ttf")), sm)
{
    systems.add <RenderSystem> (m_window);
    systems.add <PhysicsSystem>(m_window);
    systems.configure();
    m_sceneManager.setScriptManager(*sm);
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

        /*if (event.type == sf::Event::KeyPressed)
        {
            if (m_sceneManager.currentScene().name() == "TestScene")
                m_sceneManager.changeScene("TestScene2");
            else
                m_sceneManager.changeScene("TestScene");
        }*/

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
    systems.update <RenderSystem> (dt.asSeconds());
    systems.update <PhysicsSystem>(dt.asSeconds());
    m_sceneManager.getScriptManager()->doString("collectgarbage() ");
}

void Application::render()
{
    m_window.clear();
    systems.system <RenderSystem> ()->render(entities);
    systems.system <PhysicsSystem>()->render();
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