#ifndef RESOURCEKEYS_HPP
#define RESOURCEKEYS_HPP

#include <Thor/Resources.hpp>
#include <TGUI/Gui.hpp>
#include <TGUI/TGUI.hpp>

namespace res {
    inline thor::ResourceKey <tgui::Gui> guiKey(const sf::Font& font, sf::RenderWindow& wnd, const std::string& name) {
        return thor::ResourceKey <tgui::Gui>(
                [&]() {
                    std::unique_ptr <tgui::Gui> ptr (new tgui::Gui(wnd));
                    ptr->setGlobalFont(font);
                    return std::move(ptr);
                },
                name);
    }
}

#endif