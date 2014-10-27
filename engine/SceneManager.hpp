#ifndef SCENEMANAGER_HPP
#define SCENEMANAGER_HPP

#include "Scene.hpp"
#include "Exception.hpp"
#include "Debug.hpp"

#include <map>

class SceneManager
{
public:
    ~SceneManager();

    void                           addScene   (const std::string& );
    void                           removeScene(const std::string& scene_name);

    void                           changeScene(const std::string& scene_name);
    Scene&                         currentScene();
    bool                           hasRunningScene() const;

    void                           setScriptManager(ScriptManager& sm);
    ScriptManager*                 getScriptManager() const;

private:
    bool                           m_checkElement(const std::string& scene_name);

    std::string                    m_currentScene;
    std::map <std::string, Scene*> m_scenes;
    ScriptManager*                 m_scriptManager;
};

#endif // SCENEMANAGER_HPP
