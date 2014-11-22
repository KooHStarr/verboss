#ifndef SCENE_HPP
#define SCENE_HPP

#include <SFML/System/Time.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Window/Event.hpp>
#include "ResourceManager.hpp"
#include "Debug.hpp"
#include "Globals.hpp"

class Scene
{
public:
    Scene(const std::string& scene_name);

    void        load();
    void        update(sf::Time dt);
    void        render(sf::RenderTarget& target);
    void        cleanup();

    std::string name() const;

private:
    std::string           m_sceneName;
    luabridge::LuaRef     m_luaScene;
};

#endif // SCENE_HPP
