#ifndef GAMEDIRECTOR_HPP
#define GAMEDIRECTOR_HPP

#include "Application.hpp"
#include "EntityWrapper.hpp"
#include "Debug.hpp"

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <TGUI/TGUI.hpp>

class GameDirector
{
public:
    GameDirector();

    void           run();
    void DEBUGrun();

    void           setApp(Application& app);
    void           setFileSystem(FileSystem& fs);

    void           timePerFrame(sf::Time t);
    sf::Time       timePerFrame() const;

    SceneManager&  scenes();
    void           outputError(const std::string& message);

public:
    void            m_bind2Lua();

    Application*    m_app;
    sf::Time        m_timePerFrame;
    FileSystem*     m_fileSystem;
};

#endif // GAMEDIRECTOR_HPP
