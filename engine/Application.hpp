#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include "SceneManager.hpp"
#include "LuaConsole.hpp"

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>


class Application
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

    bool              isOpen() const;

private:
    sf::RenderWindow m_window;
    ResourceManager  m_resourceManager;
    LuaConsole       m_console;
    SceneManager     m_sceneManager;
};

#endif // APPLICATION_HPP
