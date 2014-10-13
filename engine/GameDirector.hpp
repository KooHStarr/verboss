#include "Application.hpp"

#ifndef GAMEDIRECTOR_HPP
#define GAMEDIRECTOR_HPP

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

class Application;

class GameDirector
{
public:

    void           run();

    void           setApp(Application& app);
    void           timePerFrame(sf::Time t);
    sf::Time       timePerFrame() const;

private:
    Application*   m_app;
    sf::Time       m_timePerFrame;
};

#endif // GAMEDIRECTOR_HPP
