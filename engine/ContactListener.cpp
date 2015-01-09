#include "ContactListener.hpp"

/////////////////////////////////////////////////////
void ContactListener::BeginContact(b2Contact* contact)
{
    global.scriptManager.doString("vgb.eventHandle = {}");
    luabridge::LuaRef event = global.vgbLuaNamespace["eventHandle"];

    b2Fixture* left = contact->GetFixtureA();
    b2Fixture* right= contact->GetFixtureB();

    event["type"] = "CollisionBegan";
    event["left"] = left;
    event["right"]= right;

    for (auto& handle : m_callbacks)
        handle.second(event);
}


/////////////////////////////////////////////////////
void ContactListener::EndContact(b2Contact* contact)
{
    global.scriptManager.doString("vgb.eventHandle = {}");
    luabridge::LuaRef event = global.vgbLuaNamespace["eventHandle"];

    b2Fixture* left = contact->GetFixtureA();
    b2Fixture* right= contact->GetFixtureB();

    event["type"] = "CollisionEnd";
    event["left"] = left;
    event["right"]= right;

    for (auto& handle : m_callbacks)
        handle.second(event);
}


/////////////////////////////////////////////////////////////////////////////////////
void ContactListener::addCallback(const std::string& name, luabridge::LuaRef callback)
{
    m_callbacks.insert (std::make_pair(name, callback));
}