#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <SFML/Graphics.hpp>
#include <functional>

#include "EntityWrapper.hpp"
#include "EntityComponents/CustomPropertyComponent.hpp"


class Camera
{
public:
    Camera(sf::RenderWindow& window);

    void update();
    void centerViewEntity(EntityWrapper wrapper);
    void reset();

private:
    sf::RenderWindow&               m_window;
    sf::View                        m_view;
    std::function <void(sf::View&)> m_callback;
};

#endif