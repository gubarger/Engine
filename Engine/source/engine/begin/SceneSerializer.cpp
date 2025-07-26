#include "SceneSerializer.h"
#include <fstream>

void SceneSerializer::Serialize(const Scene& scene, const std::string& filePath) {
	json j;

	j["name"] = scene.GetName();

	// Serialization of objects
    json objects = json::array();

    for (const auto& obj : scene.GetObjects())
    {
        json jobj;
    
        jobj["name"] = obj->GetName();
        jobj["type"] = static_cast<int>(obj->GetType());

        const auto& pos = obj->GetPosition();
        
        jobj["position"] = { pos.x, pos.y, pos.z };

        objects.push_back(jobj);
    }
    j["objects"] = objects;

    std::ofstream o(filePath);
    
    o << j.dump(4) << "\n";
}

std::shared_ptr<Scene> SceneSerializer::Deserialize(const std::string& filePath) {
    std::ifstream i(filePath);

    if (!i.is_open()) return nullptr;

    json j;
    i >> j;

    auto scene = std::make_shared<Scene>();
    
    scene->SetName(j["name"]);

    for (const auto& jobj : j["objects"]) 
    {
        std::string name = jobj["name"];
        ObjectType type = static_cast<ObjectType>(jobj["type"]);

        auto obj = std::make_shared<GameObject>(name, type);
        auto pos = jobj["position"];

        obj->SetPosition({ pos[0], pos[1], pos[2] });
        scene->AddObject(obj);
    }

    return scene;
}