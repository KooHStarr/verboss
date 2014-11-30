#include "LuaConsole.hpp"

LuaConsole::LuaConsole(Application* app, sf::Font& font) :
    m_app(app),
    m_gui(app->window()),
    m_isActive(false)
{
    m_gui.setGlobalFont(font);

    tgui::ChildWindow::Ptr childWindow(m_gui, "window");
    childWindow->load("widgets/Black.conf");
    childWindow->setTransparency(50);
    childWindow->setSize(500, 400);
    childWindow->setBackgroundColor(sf::Color(50, 50, 50, 50));
    childWindow->setCallbackId(0);
    childWindow->bindCallback(tgui::ChildWindow::Closed);

    tgui::ChatBox::Ptr chatBox(*childWindow, "chatBox");
    chatBox->load("widgets/Black.conf");
    chatBox->setSize(500, 375);
    chatBox->setTextSize(15);
    chatBox->setTransparency(50);
    chatBox->setBackgroundColor(sf::Color(50, 50, 50, 50));
    chatBox->setLineLimit(20);
    chatBox->setTextColor(sf::Color::White);
    m_chatBox = chatBox.get();

    tgui::EditBox::Ptr editBox(*childWindow, "editBox");
    editBox->load("widgets/Black.conf");
    editBox->setPosition(0, 375);
    editBox->setSize(500, 25);
    editBox->setTransparency(50);
    editBox->setTextSize(15);
    editBox->setMaximumCharacters(70);
    editBox->setTextColor(sf::Color::White);
    editBox->setSelectedTextColor(sf::Color::White);
    editBox->setSelectedTextBackgroundColor(sf::Color(225, 20, 20, 50));
    editBox->setSelectionPointColor(sf::Color::Red);
    editBox->setCallbackId(1);
    editBox->bindCallback(tgui::EditBox::ReturnKeyPressed);
    m_editBox = editBox.get();

    global.scriptManager.doString("function cls() os.execute('cls') end");
}

void LuaConsole::handleEvent(sf::Event& event)
{
    if (event.type == sf::Event::KeyPressed)
    {
        if (event.key.code == sf::Keyboard::Tilde)
            m_toggleConsole();


        if (event.key.code == sf::Keyboard::Return && m_isActive)
        {
            m_chatBox->removeAllLines();
            global.stdCapture.EndCapture();
            m_captured += global.stdCapture.GetCapture();
            std::cout << m_captured.size() << "\n";
            m_chatBox->addLine(m_captured);
            global.stdCapture.BeginCapture();
        }
    }

    if (m_isActive)
        m_gui.handleEvent(event);
}

void LuaConsole::update(sf::Time dt)
{
    if (m_isActive)
        m_handleCallbacks();
}

void LuaConsole::render()
{
    if (m_isActive)
        m_gui.draw();
}

void LuaConsole::m_toggleConsole()
{
    m_isActive = !m_isActive;

    if (!m_isActive)
        m_gui.unfocusWidgets();
}

void LuaConsole::m_handleCallbacks()
{
    tgui::Callback c;

    while (m_gui.pollCallback(c))
    {
        if (c.id == 0)
            m_toggleConsole();

        if (c.id == 1)
        {
            std::string command = m_editBox->getText();

            try {
                m_chatBox->addLine(command);
                m_checkCommand(command);
                global.scriptManager.doString(command);
            } catch (Exception& e) {
                /*add lines with color*/
                m_chatBox->addLine(e.what());
            }
            m_editBox->setText("");
        }
    }
}

void LuaConsole::m_checkCommand(const std::string& command)
{
    if (command.find("cls()") != std::string::npos)
    {
        m_chatBox->removeAllLines();
        m_captured = "";
    }
}