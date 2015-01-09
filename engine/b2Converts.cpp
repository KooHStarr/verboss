#include "b2Converts.hpp"

/////////////////////////
float si::meters(float p)
{
    return tmx::SfToBoxFloat(p);
}
/*
sf::Vector2f si::meters(const b2Vec2& p)
{
    return
    //return sf::Vector2f(p.x / pixelsPerMeter, -p.y / pixelsPerMeter);
}*/

///////////////////////////////////////
b2Vec2 si::meters(const sf::Vector2f& p)
{
    return tmx::SfToBoxVec(p);
    //return b2Vec2(p.x / pixelsPerMeter, -p.y / pixelsPerMeter);
}


///////////////////////////////////
b2Vec2 si::meters(float x, float y)
{
    return tmx::SfToBoxVec(sf::Vector2f(x, y));
}

////////////////////////////
float si::pixels(float m)
{
    return tmx::BoxToSfFloat(m);
    //return m * pixelsPerMeter;
}


////////////////////////////////////////
sf::Vector2f si::pixels(const b2Vec2& m)
{
    return tmx::BoxToSfVec(m);
    //return sf::Vector2f(m.x * pixelsPerMeter, -m.y * pixelsPerMeter);
}


////////////////////////////////////////
sf::Vector2f si::pixels(float x, float y)
{
    return tmx::BoxToSfVec(b2Vec2(x, y));
}

