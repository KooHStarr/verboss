#include "Application.hpp"

Application::Application() :
    m_window(sf::VideoMode(800, 600), "alpha")
{

}

void Application::addScene(const std::string& scene_name)
{
    m_sceneManager.addScene(scene_name);
}

void Application::update(sf::Time dt)
{
    m_sceneManager.currentScene()->update(dt);
}

void Application::render()
{
    m_window.clear();
    m_sceneManager.currentScene()->render(m_window);
    m_window.display();
}
