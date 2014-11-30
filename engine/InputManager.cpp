#include <Thor/Graphics/ToString.hpp>
#include "InputManager.hpp"

void InputManager::addController(EntityWrapper wrapper, const std::string& tablename)
{
    ControllerComponent::Handle chandle = wrapper.getEntity().assign <ControllerComponent> ();
    chandle->inputTable = global.scriptManager.getGlobal(tablename);
    chandle->inputTableName = tablename;

    m_bindActions(wrapper);
}

void InputManager::invokeCallbacks(sf::RenderWindow& window)
{
    m_actionMap.invokeCallbacks(m_callbackSystem, &window);
}

InputManager::TActionMap& InputManager::getActionMap()
{
    return m_actionMap;
}

InputManager::TCallbackSystem& InputManager::getCallbackSystem()
{
    return m_callbackSystem;
}

void InputManager::m_bindActions(EntityWrapper wrapper)
{
    ControllerComponent::Handle chandle = wrapper.getEntity().component <ControllerComponent> ();
    luabridge::LuaRef inputHandle = chandle->inputTable;

    /*UGLY HACK TO ITERATE THOUGH TABLE VERY DIRTY...*/
    std::string temp = "function detail_hackFunc() for k, _ in pairs(" + chandle->inputTableName + ") do vgb.controller:detail_addTableNameKey(k) end end";
    global.scriptManager.doString(temp);
    luabridge::LuaRef hackFunc = global.scriptManager.getGlobal("detail_hackFunc");
    hackFunc();
    hackFunc = luabridge::Nil();

    for (auto& actionname : m_keyBuff)
    {
        luabridge::LuaRef actionHandle = inputHandle[actionname];
        luabridge::LuaRef funcHandle = actionHandle["callback"];

        if (actionHandle["hid"] == "keyboard") {
            try {
                sf::Keyboard::Key key = thor::toKeyboardKey(actionHandle["key"]);
                std::string actionType = actionHandle["actionType"].cast <std::string> ();
                thor::Action::ActionType ID = thor::Action::Hold;

                if (actionType == "pressOnce")
                    ID = thor::Action::PressOnce;
                else if (actionType == "releaseOnce")
                    ID = thor::Action::ReleaseOnce;
                else if (actionType == "hold")
                    ID = thor::Action::Hold;
                else
                    std::cout << "<InputManager::addAction> no actionType specified\n";

                m_actionMap[chandle->inputTableName + actionname] = thor::Action(key, ID);
                m_callbackSystem.connect(chandle->inputTableName + actionname, [funcHandle, wrapper](thor::ActionContext<std::string> context) {
                    funcHandle(wrapper);
                });

            } catch (const thor::StringConversionException &e) {
                //W+E
            }
        }
        if (actionHandle["hid"] == "joystick") {

        }

        if (actionHandle["hid"] == "mouse") {

        }
    }

    m_keyBuff.clear();
}