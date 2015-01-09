#ifndef INPUTMANAGER_HPP
#define INPUTMANAGER_HPP

#include <Thor/Input.hpp>
#include <sstream>
#include <unordered_map>
#include "EntityComponents/ControllerComponent.hpp"
#include "EntityWrapper.hpp"
#include "Globals.hpp"
#include "Helpers.hpp"

class InputManager
{
public:
    typedef thor::ActionMap <std::string> TActionMap;
    typedef TActionMap::CallbackSystem    TCallbackSystem;

    void               addController(EntityWrapper wrapper, const std::string& tablename);
    void               handleEvent(const sf::Event& event);

    //void               addEventCallback(luabridge::LuaRef callback);
    //void               removeEventCallback(luabridge::LuaRef callback);
    void               addEventCallback(lua_State* callback);
    void               removeEventCallback(lua_State* callback);//

    void               invokeCallbacks(sf::RenderWindow& window);
    TActionMap&        getActionMap();
    TCallbackSystem&   getCallbackSystem();

private:
    void                      m_bindActions(EntityWrapper wrapper);
    void                      m_addKeyboardActions(luabridge::LuaRef actionHandle, const std::string& actionname, EntityWrapper wrapper);
    void                      m_addMouseActions   (luabridge::LuaRef actionHandle, const std::string& actionname, EntityWrapper wrapper);
    void                      m_addJoystickActions(luabridge::LuaRef actionHandle, const std::string& actionname, EntityWrapper wrapper);

    TActionMap                                          m_actionMap;
    TCallbackSystem                                     m_callbackSystem;
    std::unordered_map <std::string, luabridge::LuaRef> m_eventCallbacks;
};

#endif