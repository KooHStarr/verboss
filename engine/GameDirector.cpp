#include "GameDirector.hpp"

void GameDirector::run()
{
    sf::Clock clock;
    sf::Time timeSinceLastUpdate = sf::Time::Zero;

    while (m_app->m_window.isOpen())
    {
        sf::Time dt = clock.restart();
        timeSinceLastUpdate += dt;

        while (timeSinceLastUpdate > m_timePerFrame)
        {
            timeSinceLastUpdate -= m_timePerFrame;
            m_app->update(m_timePerFrame);
        }

        m_app->render();
    }
}


void GameDirector::setApp(Application& app)
{
    m_app = &app;
}


void GameDirector::timePerFrame(sf::Time t)
{
    m_timePerFrame = t;
}


sf::Time GameDirector::timePerFrame() const
{
    return m_timePerFrame;
}
