#ifndef INPUTMANAGER_HPP
#define INPUTMANAGER_HPP

#include <Thor/Input.hpp>
#include "EntityComponents/ControllerComponent.hpp"
#include "EntityWrapper.hpp"
#include "Globals.hpp"

class InputManager
{
public:
    typedef thor::ActionMap <std::string> TActionMap;
    typedef TActionMap::CallbackSystem    TCallbackSystem;

    void               addController(EntityWrapper wrapper, const std::string& tablename);
    void               invokeCallbacks(sf::RenderWindow& window);
    TActionMap&        getActionMap();
    TCallbackSystem&   getCallbackSystem();

    void detail_addTableNameKey(const std::string& key) { m_keyBuff.push_back(key); }

private:
    void                      m_bindActions(EntityWrapper wrapper);

    std::vector <std::string> m_keyBuff;
    TActionMap                m_actionMap;
    TCallbackSystem           m_callbackSystem;
};

#endif