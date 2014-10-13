#include "SceneManager.hpp"


void SceneManager::addScene(const std::string& scene_name)
{
    if (m_checkElement(scene_name))
        throw Exception("[From C++] <SceneManager::addScene> Scene with name '" +
                        scene_name + "' already exists!");

    //m_scriptManager.doFile(scene_name);
}


void SceneManager::removeScene(const std::string& scene_name)
{
    if (!m_checkElement(scene_name))
        throw Exception("[From C++] <SceneManager::removeScene> Scene with name '" +
                        scene_name + "' doesn't exists!");

    //m_scriptManager.doString(scene_name + " = nil\n");
    //m_scenes.erase(scene_name);
}


const std::string& SceneManager::currentSceneName() const
{
    return m_currentScene;
}

Scene* SceneManager::currentScene()
{
    return m_scenes[currentSceneName()];
}

void SceneManager::currentSceneName(const std::string& scene_name)
{
    if (!m_checkElement(scene_name))
        throw Exception("[From C++] <SceneManager::removeScene> Scene with name '" +
                        scene_name + "' doesn't exists!");

    m_currentScene = scene_name;
}


bool SceneManager::m_checkElement(const std::string& scene_name)
{
    auto found = m_scenes.find(scene_name);
    return found != m_scenes.end();
}
