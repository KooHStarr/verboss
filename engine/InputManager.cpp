#include <Thor/Graphics/ToString.hpp>
#include "InputManager.hpp"

/////////////////////////////////////////////////////////////////////////////////////
void InputManager::addController(EntityWrapper wrapper, const std::string& tablename)
{
    ControllerComponent::Handle chandle = wrapper.getEntity().assign <ControllerComponent> ();
    chandle->inputTable = global.scriptManager.getGlobal(tablename);
    chandle->inputTableName = tablename;

    m_bindActions(wrapper);
}


/////////////////////////////////////////////////////////////
void InputManager::invokeCallbacks(sf::RenderWindow& window)
{
    m_actionMap.invokeCallbacks(m_callbackSystem, &window);
}


//////////////////////////////////////////////////////
InputManager::TActionMap& InputManager::getActionMap()
{
    return m_actionMap;
}


////////////////////////////////////////////////////////////////
InputManager::TCallbackSystem& InputManager::getCallbackSystem()
{
    return m_callbackSystem;
}


///////////////////////////////////////////////////////
void InputManager::m_bindActions(EntityWrapper wrapper)
{
    ControllerComponent::Handle chandle = wrapper.getEntity().component <ControllerComponent> ();
    luabridge::LuaRef inputHandle = chandle->inputTable;

    m_fillKeyBuffFromLua(chandle->inputTableName);

    for (auto& actionname : m_keyBuff)
    {
        luabridge::LuaRef actionHandle = inputHandle[actionname];

        if (actionHandle["hid"] == "keyboard")
            m_addKeyboardActions(actionHandle, actionname, wrapper);

        else if (actionHandle["hid"] == "joystick")
            m_addJoystickActions(actionHandle, actionname, wrapper);

        else if (actionHandle["hid"] == "mouse")
            m_addMouseActions(actionHandle, actionname, wrapper);

        //else throw big exception
    }

    m_keyBuff.clear();
}


/////////////////////////////////////////////////////////////////////
void InputManager::m_fillKeyBuffFromLua(const std::string& tablename)
{
    /*UGLY HACK TO ITERATE THOUGH TABLE VERY DIRTY...*/
    std::string temp = "function detail_hackFunc() for k, _ in pairs(" + tablename + ") do vgb.input:detail_addTableNameKey(k) end end";
    global.scriptManager.doString(temp);
    luabridge::LuaRef hackFunc = global.scriptManager.getGlobal("detail_hackFunc");
    hackFunc();
    hackFunc = luabridge::Nil();
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void InputManager::m_addKeyboardActions(luabridge::LuaRef actionHandle, const std::string& actionname, EntityWrapper wrapper)
{
    luabridge::LuaRef funcHandle = actionHandle["callback"];
    ControllerComponent::Handle chandle = wrapper.getEntity().component <ControllerComponent> ();

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

        //add complex key actions, separated by '|', '&' (or, and)
    } catch (const thor::StringConversionException &e) {
        std::cout << "Here, cause '" << actionHandle["key"].cast <std::string> () << "'\n";
        /*std::vector <std::string> tokens;
        std::string delimiter_or = "|";
        std::string delimiter_and = "&";
        std::string source = actionHandle["key"];

        int pos = 0;
        std::string token;

        while ((pos = source.find(delimiter)) != std::string::npos) {
            token = source.substr(0, pos);
            std::cout << token << std::endl;
            source.erase(0, pos + delimiter.length());
        }*/
    }
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void InputManager::m_addMouseActions(luabridge::LuaRef actionHandle, const std::string& actionname, EntityWrapper wrapper)
{}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void InputManager::m_addJoystickActions(luabridge::LuaRef actionHandle, const std::string& actionname, EntityWrapper wrapper)
{}


//////////////////////////////////////////////////////////
void InputManager::addEventCallback(lua_State* callback)
{
    luabridge::LuaRef func = luabridge::LuaRef::fromStack(callback, -1);
    std::string val = func.tostring();

    m_eventCallbacks.insert(std::make_pair(val, func));
}


////////////////////////////////////////////////////////////
void InputManager::removeEventCallback(lua_State* callback)
{
    /*std::cout << "REmoving...\n";
    luabridge::LuaRef func = luabridge::LuaRef::fromStack(callback, -1);
    std::cout << "Finding the same callback\n";
    std::string left = func.tostring();
    m_eventCallbacks.erase(std::find(std::begin(m_eventCallbacks), std::end(m_eventCallbacks),
            [&] (const std::pair <std::string, luabridge::LuaRef> &val)
            {
                return val.first == left;
            }));*/
}


/////////////////////////////////////////////////
void InputManager::handleEvent(const sf::Event& event)
{
    m_actionMap.pushEvent(event);

    global.scriptManager.doString("vgb.eventHandle = {}");
    luabridge::LuaRef eventHandle = global.vgbLuaNamespace["eventHandle"];
    eventHandle["type"] = "Unknown";
    bool mouseUsed = false;
    bool mouseButtonUsed = false;

    // add more events
    switch (event.type)
    {
        case sf::Event::KeyPressed:
            eventHandle["type"] = "KeyPressed";
            break;

        case sf::Event::MouseMoved:
            eventHandle["type"] = "MouseMoved";
            mouseUsed = true;
            break;

        case sf::Event::MouseButtonPressed:
            eventHandle["type"] = "MouseButtonPressed";
            mouseUsed = true;
            mouseButtonUsed = true;
            break;

        case sf::Event::MouseButtonReleased:
            eventHandle["type"] = "MouseButtonReleased";
            mouseUsed = true;
            mouseButtonUsed = true;
            break;
    }

    //global.scriptManager.doString("vgb.eventHandle.mouse = {}");
    if (mouseUsed)
    {
        luabridge::LuaRef mouseHandle = eventHandle["mouse"];

        if (mouseButtonUsed)
            mouseHandle["button"] = thor::toString(event.mouseButton.button);

        mouseHandle["x"] = event.mouseButton.x;
        mouseHandle["y"] = event.mouseButton.y;
    }

    for (auto& handle : m_eventCallbacks)
        handle.second(eventHandle);
}