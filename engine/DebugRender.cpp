#include "Render.hpp"
#include <stdio.h>
#include <stdarg.h>

namespace
{
    inline sf::Color b2tosfColor(const b2Color& c)
    {
        return sf::Color(c.r * 255, c.g * 255, c.b * 255);
    }
}

sf::DebugDraw::DebugDraw(sf::RenderTarget& target) :
    m_target(target)
{
}

void sf::DebugDraw::DrawPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color)
{
    sf::VertexArray outline(sf::LinesStrip, vertexCount);

    for (auto i = 0; i < vertexCount; i++)
    {
        outline[i].position = si::pixels(vertices[i]);
        outline[i].color    = b2tosfColor(color);;
    }

    m_target.draw(outline);
}

void sf::DebugDraw::DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color)
{
    sf::VertexArray outline(sf::LinesStrip, vertexCount);
    sf::VertexArray shape(sf::TrianglesFan, vertexCount);

    for (auto i = 0; i < vertexCount; i++)
    {
        auto c = b2tosfColor(color);

        outline[i].position = si::pixels(vertices[i]);
        outline[i].color    = c;

        shape[i].position   = si::pixels(vertices[i]);
        shape[i].color      = sf::Color(c.r / 2, c.g / 2, c.b / 2, 100);
    }

    m_target.draw(shape);
    m_target.draw(outline);
}

void sf::DebugDraw::DrawCircle(const b2Vec2& center, float32 radius, const b2Color& color)
{
    sf::CircleShape circle(radius);
    circle.setPosition(si::pixels(center));
    circle.setFillColor(b2tosfColor(color));

    m_target.draw(circle);
}

void sf::DebugDraw::DrawSolidCircle(const b2Vec2& center, float32 radius, const b2Vec2& axis, const b2Color& color)
{
    float32 r = si::pixels(radius);
	sf::CircleShape circle(r);
	sf::Vector2f pos(si::pixels(center));
    circle.setPosition(pos.x - r, pos.y - r);
    sf::Color c = b2tosfColor(color);
    circle.setFillColor(sf::Color(0.5 * c.r, 0.5 * c.g, 0.5 * c.b, 100));
    circle.setOutlineThickness(1);
    circle.setOutlineColor(c);

    m_target.draw(circle);
}

void sf::DebugDraw::DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color)
{
    sf::VertexArray array(sf::Lines, 2);

    array[0].position = si::pixels(p1);
    array[0].color    = b2tosfColor(color);

    array[1].position = si::pixels(p2);
    array[1].color    = b2tosfColor(color);

    m_target.draw(array);
}

void sf::DebugDraw::DrawTransform(const b2Transform& xf)
{
}

void sf::DebugDraw::DrawPoint(const b2Vec2& p, float32 size, const b2Color& color)
{

}

void sf::DebugDraw::DrawString(int x, int y, const char *string, ...)
{
	char buffer[128];

	va_list arg;
	va_start(arg, string);
	vsprintf(buffer, string, arg);
	va_end(arg);
}

void sf::DebugDraw::DrawString(const b2Vec2& p, const char *string, ...)
{
}

void sf::DebugDraw::DrawAABB(b2AABB* aabb, const b2Color& c)
{
}
