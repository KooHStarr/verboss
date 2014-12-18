#include "GameDirector.hpp"

void GameDirector::run()
{
   // m_bind2Lua();
    {
        LuaBinder binder;
        binder.bind(this);
    }

    global.scriptManager.doFile("main.lua");

    sf::Clock clock;
    sf::Time timeSinceLastUpdate = sf::Time::Zero;

    while (m_app->isOpen())
    {
        sf::Time dt = clock.restart();
        timeSinceLastUpdate += dt;

        while (timeSinceLastUpdate > m_timePerFrame)
        {
            timeSinceLastUpdate -= m_timePerFrame;
            m_app->event();
            m_app->update(m_timePerFrame);
        }

        m_app->render();
    }
}


void GameDirector::setApp(Application& app)
{
    m_app = &app;
}

Application& GameDirector::getApp()
{
    return *m_app;
}


void GameDirector::timePerFrame(sf::Time t)
{
    m_timePerFrame = t;
}

SceneManager& GameDirector::scenes()
{
    return m_app->scenes();
}

sf::Time GameDirector::timePerFrame() const
{
    return m_timePerFrame;
}

void GameDirector::outputError(const std::string& message)
{
    //m_app->m_window.create(sf::VideoMode(800, 600), "Error!");

    /*TODO nice error GUI**/
}


void GameDirector::DEBUGrun()
{
   // m_bind2Lua();

    //namespace ex = entityx;

    sf::RenderWindow& window = m_app->window();
    LuaConsole console(m_app, *m_app->resourceManager().load <sf::Font> ("font", thor::Resources::fromFile <sf::Font> ("assets/font.ttf")));
    //ex::Entity ent;
    //ent.assign <GraphicsComponent> ();
    //GraphicsComponent::Handle handle = ent.component <GraphicsComponent> ();


    while (window.isOpen())
    {
        sf::Event event;

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            console.handleEvent(event);
        }

        m_app->systems.update <RenderSystem> (1.f / 60.f);

        console.update(sf::seconds(1.f / 60.f));
        window.clear();
        console.render();
        window.display();
    }
}