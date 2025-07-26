#include "SceneManager.h"

SceneManager& SceneManager::GetInstance() {
    static SceneManager instance;
    
    return instance;
}

void SceneManager::AddScene(std::shared_ptr<Scene> scene) {
    m_scenes.push_back(scene);
    
    if (!m_activeScene)
    {
        m_activeScene = scene;
    }
}

void SceneManager::RemoveScene(const std::string& name) {
    for (auto it = m_scenes.begin(); it != m_scenes.end(); ++it) 
    {
        if ((*it)->GetName() == name)
        {
            if (m_activeScene == *it) 
            {
                m_activeScene = m_scenes.empty() ? nullptr : m_scenes[0];
            }

            m_scenes.erase(it);
            return;
        }
    }
}

void SceneManager::SetActiveScene(const std::string& name) {
    for (auto& scene : m_scenes)
    {
        if (scene->GetName() == name)
        {
            m_activeScene = scene;
            return;
        }
    }
}