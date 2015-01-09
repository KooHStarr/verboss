#ifndef CONTACTLISTENER_HPP
#define CONTACTLISTENER_HPP

#include <Box2D/Box2D.h>
#include <unordered_map>
#include "Globals.hpp"

class ContactListener : public b2ContactListener
{
public:
    virtual void BeginContact(b2Contact* contact);
    virtual void EndContact  (b2Contact* contact);
    virtual void PreSolve    (b2Contact* contact, const b2Manifold* oldManifold)   {}
    virtual void PostSolve   (b2Contact* contact, const b2ContactImpulse* impulse) {}

    void addCallback(const std::string& name, luabridge::LuaRef callback);

private:
    std::unordered_map <std::string, luabridge::LuaRef> m_callbacks;
};

#endif