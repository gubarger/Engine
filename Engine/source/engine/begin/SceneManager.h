#pragma once

#include <vector>
#include <memory>
#include "Scene.h"

class SceneManager {
public:
    static SceneManager& GetInstance();

    void AddScene(std::shared_ptr<Scene> scene);
    void RemoveScene(const std::string& name);
    void SetActiveScene(const std::string& name);

    std::shared_ptr<Scene> GetActiveScene() const { return m_activeScene; }
    const std::vector<std::shared_ptr<Scene>>& GetScenes() const { return m_scenes; }

private:
    SceneManager() = default;

private:
    std::vector<std::shared_ptr<Scene>> m_scenes;
    std::shared_ptr<Scene> m_activeScene = nullptr;
};