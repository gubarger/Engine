#pragma once

/**
        @Still a raw implementation, it will be finalized in the future.
*/

#include <nlohmann/json.hpp>
#include "Scene.h"

using json = nlohmann::json;

class SceneSerializer {
public:
    static void Serialize(const Scene& scene, const std::string& filePath);
    static std::shared_ptr<Scene> Deserialize(const std::string& filePath);

};