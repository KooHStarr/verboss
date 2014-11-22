#ifndef RESOURCEKEYS_HPP
#define RESOURCEKEYS_HPP

#include <Thor/Resources.hpp>
#include <TGUI/Gui.hpp>
#include <tmx/MapLoader.h>

namespace res {
    inline thor::ResourceKey <tgui::Gui> guiKey(const sf::Font& font, sf::RenderWindow& wnd, const std::string& name)
    {
        return thor::ResourceKey <tgui::Gui>(
                [&]() {
                    std::unique_ptr <tgui::Gui> ptr (new tgui::Gui(wnd));
                    ptr->setGlobalFont(font);
                    return std::move(ptr);
                },
                name);
    }

    inline thor::ResourceKey <tmx::MapLoader> tileMapKey(const std::string& mapname)
    {
        return thor::ResourceKey <tmx::MapLoader>(
                [&]() {
                    //here load mapname with filesystem
                    std::unique_ptr <tmx::MapLoader> ptr (new tmx::MapLoader("assets/"));
                    //here add all search paths to the map loader
                    ptr->Load(mapname);
                    return std::move(ptr);
                },
                mapname);
    }
}

#endif