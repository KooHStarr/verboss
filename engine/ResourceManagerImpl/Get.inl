template <>
inline std::shared_ptr <sf::Texture> ResourceManager::get <sf::Texture> (const ID& name)
{
    return m_textureHolder.get(name);
}

template <>
inline std::shared_ptr <sf::Shader> ResourceManager::get <sf::Shader> (const ID& name)
{
    return m_shaderHolder.get(name);
}

template <>
inline std::shared_ptr <tgui::Gui> ResourceManager::get <tgui::Gui> (const ID& name)
{
    return m_guiHolder.get(name);
}

template <>
inline std::shared_ptr <sf::Font> ResourceManager::get <sf::Font> (const ID& name)
{
    return m_fontHolder.get(name);
}