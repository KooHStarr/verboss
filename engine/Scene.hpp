#ifndef SCENE_HPP
#define SCENE_HPP

#include <SFML/System/Time.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

class Scene
{
public:
    virtual ~Scene() {}

    virtual void update(sf::Time dt) = 0;
    virtual void render(sf::RenderTarget& target) = 0;
};

#endif // SCENE_HPP
