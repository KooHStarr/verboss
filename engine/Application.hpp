#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include "SceneManager.hpp"
#include "EntitySystems/RenderSystem.hpp"
#include "EntitySystems/PhysicsSystem.hpp"
#include "LuaConsole.hpp"

#include <Box2d/Box2d.h>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <entityx/entityx.h>

class Application : public entityx::EntityX
{
public:
    //Application(Settings& s)
    Application(ScriptManager* sm);

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
