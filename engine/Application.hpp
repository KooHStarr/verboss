#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include "SceneManager.hpp"
#include "RenderSystem.hpp"
#include "EntityManagerWrapper.hpp"
#include "LuaConsole.hpp"
#include "InputManager.hpp"
#include "Camera.hpp"
#include "FileSystem.hpp"

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <entityx/entityx.h>

class LuaConsole;

class Application : public entityx::EntityX
{
public:
    //Application(Settings& s)
    Application();

    void              event();
    void              update(sf::Time dt);
    void              render();

    ResourceManager&  resourceManager();
    SceneManager&     scenes();
    sf::RenderWindow& window();
    InputManager&     input();
    Camera&           camera();
    FileSystem&       fileSystem();

    bool              isOpen() const;

private:
    void m_initSystems();

    sf::RenderWindow m_window;
    ResourceManager  m_resourceManager;
    LuaConsole       m_console;
    SceneManager     m_sceneManager;
    InputManager     m_inputManager;
    FileSystem       m_fileSystem;
    Camera           m_camera;
};

#endif // APPLICATION_HPP
