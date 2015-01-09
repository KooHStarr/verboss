#include "Application.hpp"

Application::Application() :
    m_window(sf::VideoMode(800, 600), "alpha"),
    m_console(this, *m_resourceManager.load <sf::Font> ("default", thor::Resources::fromFile <sf::Font> ("assets/font.ttf"))),
    m_fileSystem(__argv),
    m_camera(m_window)
{
    m_window.setKeyRepeatEnabled(false);
    m_initSystems();
}

void Application::event()
{
    m_inputManager.getActionMap().clearEvents();
    sf::Event event;

    while (m_window.pollEvent(event))
    {
        m_inputManager.handleEvent(event);
        m_console.handleEvent(event);

        if (event.type == sf::Event::Closed)
            m_window.close();
    }

    m_inputManager.invokeCallbacks(m_window);
}

void Application::update(sf::Time dt)
{
    m_sceneManager.currentScene().update(dt);
    m_console.update(dt);
    m_camera.update();
    systems.update <RenderSystem>   (dt.asSeconds());
    systems.update <AnimationSystem>(dt.asSeconds());
    systems.update <PhysicsSystem>  (dt.asSeconds());
    systems.update <TileMapSystem>  (dt.asSeconds());
    global.scriptManager.doString("collectgarbage() ");
}

void Application::render()
{
    m_window.clear();
    systems.system <RenderSystem> ()->render();
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


InputManager& Application::input()
{
    return m_inputManager;
}

Camera& Application::camera()
{
    return m_camera;
}

FileSystem& Application::fileSystem()
{
    return m_fileSystem;
}

void Application::m_initSystems()
{
    systems.add <RenderSystem>    (m_window);
    systems.add <TileMapSystem>   ();
    systems.add <PhysicsSystem>   ();
    systems.add <AnimationSystem> ();
    systems.configure();

    systems.system <RenderSystem>    ()->setEntityManager(this);
    systems.system <TileMapSystem>   ()->setEntityManager(this);
    systems.system <PhysicsSystem>   ()->setEntityManager(this);
    systems.system <AnimationSystem> ()->setEntityManager(this);
}
