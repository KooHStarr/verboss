#include "Scene.hpp"

//////////////////////////////////////////
Scene::Scene(const std::string& scene_name) :
        m_sceneName(scene_name),
        m_luaScene(global.scriptManager.getGlobal(scene_name))
{}


/////////////////
void Scene::load()
{
    m_luaScene["load"]();
}


///////////////////////////////
void Scene::update(sf::Time dt)
{
    m_luaScene["update"](dt.asSeconds());
}


////////////////////////////////////////////
void Scene::render(sf::RenderTarget& target)
{
    m_luaScene["render"]();
}


/////////////////////
void Scene::cleanup()
{
    m_luaScene["cleanup"]();
    global.scriptManager.doString("vgb.currentGui = nil\n"
                              "vgb.detail_gui_wrapper = nil");
}


///////////////////////////////
std::string Scene::name() const
{
    return m_sceneName;
}