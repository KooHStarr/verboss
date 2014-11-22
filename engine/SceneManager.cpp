#include "SceneManager.hpp"

SceneManager::~SceneManager()
{
    for (auto& i : m_scenes)
        removeScene(i.first);
}

void SceneManager::addScene(const std::string& scene_name)
{
    if (m_checkElement(scene_name))
        throw Exception("<SceneManager::addScene>", "Scene with name '" +
                        scene_name + "' already exists!");

    global.scriptManager.doFile(scene_name + ".lua");
    m_scenes[scene_name] = new Scene(scene_name);
}


void SceneManager::removeScene(const std::string& scene_name)
{
    if (!m_checkElement(scene_name))
        throw Exception("<SceneManager::removeScene>", "Scene with name '" +
                        scene_name + "' doesn't exists!");

    m_scenes[scene_name]->cleanup();
    delete m_scenes[scene_name];
    m_scenes.erase(scene_name);
}

Scene& SceneManager::currentScene()
{
    return *m_scenes[m_currentScene];
}

void SceneManager::changeScene(const std::string& scene_name)
{
    if (!m_checkElement(scene_name))
        throw Exception("<SceneManager::changeScene>", "Scene with name '" +
                        scene_name + "' doesn't exists!");


    if (hasRunningScene())
        currentScene().cleanup();

    m_currentScene = scene_name;
    currentScene().load();
}

bool SceneManager::hasRunningScene() const
{
    return m_currentScene != "";
}


bool SceneManager::m_checkElement(const std::string& scene_name)
{
    auto found = m_scenes.find(scene_name);
    return found != m_scenes.end();
}