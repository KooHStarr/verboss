#include <tmx/tmx2box2d.h>
#include <Thor/Math.hpp>

namespace si
{

//convert pixels in meters
float meters(float p);
b2Vec2 meters(const sf::Vector2f& p);

//convert meters in pixel size
float pixels(float m);
sf::Vector2f pixels(const b2Vec2& m);

}
