template <>
inline void ResourceManager::release <sf::Texture> (const ID& name)
{
    m_textureHolder.release(name);
}

template <>
inline void ResourceManager::release <sf::Shader> (const ID& name)
{
    m_shaderHolder.release(name);
}

template <>
inline void ResourceManager::release <tgui::Gui> (const ID& name)
{
    m_guiHolder.release(name);
}

template <>
inline void ResourceManager::release <sf::Font> (const ID& name)
{
    m_fontHolder.release(name);
}