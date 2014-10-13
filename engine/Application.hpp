#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include "GameDirector.hpp"
#include "SceneManager.hpp"

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

class Application
{
    friend class GameDirector;

public:
    //Application(Settings& s)
    Application();

    void addScene(const std::string& scene_name);

    void update(sf::Time dt);
    void render();

private:
    sf::RenderWindow m_window;
    SceneManager     m_sceneManager;
};

#endif // APPLICATION_HPP
