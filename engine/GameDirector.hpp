#ifndef GAMEDIRECTOR_HPP
#define GAMEDIRECTOR_HPP

#include "LuaBinder.hpp"
#include "EntityWrapper.hpp"
#include "Debug.hpp"

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <TGUI/TGUI.hpp>

class GameDirector
{
public:
    void            run();
    void DEBUGrun();

    void            setApp(Application& app);
    Application&    getApp();

    void            timePerFrame(sf::Time t);
    sf::Time        timePerFrame() const;

    SceneManager&   scenes();
    void            outputError(const std::string& message);

public:
    Application*    m_app;
    sf::Time        m_timePerFrame;
};

#endif // GAMEDIRECTOR_HPP
