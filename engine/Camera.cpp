#include "Camera.hpp"
#include "b2Converts.hpp"

Camera::Camera(sf::RenderWindow& window) :
        m_window(window)
{
    m_view.setSize(m_window.getSize().x, m_window.getSize().y);
    m_view.setCenter(m_window.getView().getCenter().x, m_window.getView().getCenter().y);
    reset();
}

void Camera::update()
{
    m_callback(m_view);
    m_window.setView(m_view);
}

void Camera::centerViewEntity(EntityWrapper wrapper)
{
    m_callback = [=, this] (sf::View& view) mutable
    {
        b2Body* body = wrapper.getBody();
        m_view.setCenter(si::pixels(body->GetPosition()));
    };
}

void Camera::reset()
{
    m_callback = [] (sf::View&) {};
}