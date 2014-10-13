#ifndef SCENEMANAGER_HPP
#define SCENEMANAGER_HPP

#include "Scene.hpp"
#include "Exception.hpp"

#include <map>

class SceneManager
{
public:
    void                           addScene   (const std::string& scene_name);
    void                           removeScene(const std::string& scene_name);

    const std::string&             currentSceneName() const;
    void                           currentSceneName(const std::string& scene_name);
    Scene*                         currentScene();

private:
    bool                           m_checkElement(const std::string& scene_name);


    std::string                    m_currentScene;
    std::map <std::string, Scene*> m_scenes;
};

#endif // SCENEMANAGER_HPP
