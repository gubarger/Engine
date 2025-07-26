#include "ResourceManager.h"
#include "../object/Texture.h"
#include "../object/SpriteObject.h"
#include "../object/ModelObject.h"
#include <filesystem>

void ResourceManager::LoadResources(const std::string& path2D, const std::string& path3D) {
    namespace fs = std::filesystem;

    try 
    {
        if (!fs::exists(path2D)) 
        {
            std::cerr << "Directory not found: " << path2D << "\n";
            return;
        }

        if (!fs::exists(path3D)) 
        {
            std::cerr << "Directory not found: " << path3D << "\n";
            return;
        }

        // load 2d obj
        for (const auto& entry : fs::directory_iterator(path2D)) 
        {
            if (entry.is_regular_file() && entry.path().extension() == ".png")
            {
                std::string name = entry.path().stem().string();
                
                try 
                {
                    auto texture = std::make_shared<Texture>(entry.path().string());
                    auto sprite = std::make_shared<SpriteObject>(name, texture);

                    m_2DObjects.push_back(sprite);
                    m_resourceTemplates[name] = sprite;
                }
                catch (const std::exception& e)
                {
                    std::cerr << "Failed to load texture: " << entry.path() << " - " << e.what() << "\n";
                }
            }
        }

        // load 3d obj
        for (const auto& entry : fs::directory_iterator(path3D)) 
        {
            if (entry.is_regular_file() && entry.path().extension() == ".obj") 
            {
                std::string name = entry.path().stem().string();
            
                try
                {
                    auto model = std::make_shared<Model>(entry.path().string());
                    auto modelObj = std::make_shared<ModelObject>(name, model);
                
                    m_3DObjects.push_back(modelObj);
                    m_resourceTemplates[name] = modelObj;
                }
                catch (const std::exception& e) 
                {
                    std::cerr << "Failed to load model: " << entry.path() << " - " << e.what() << "\n";
                }
            }
        }
    }
    catch (const fs::filesystem_error& e)
    {
        std::cerr << "Filesystem error: " << e.what() << "\n";
    }
}

std::shared_ptr<GameObject> ResourceManager::CreateInstance(const std::string& resourceName) {
    if (m_resourceTemplates.find(resourceName) != m_resourceTemplates.end()) 
    {
        auto original = m_resourceTemplates[resourceName];

        if (auto sprite = std::dynamic_pointer_cast<SpriteObject>(original))
        {
            auto newSprite = std::make_shared<SpriteObject>(
                resourceName + "_instance",
                sprite->GetTexture()
            );

            newSprite->SetPosition(sprite->GetPosition());
            newSprite->SetRotation(sprite->GetRotation());
            newSprite->SetScale(sprite->GetScale());

            return newSprite;
        }
        else if (auto model = std::dynamic_pointer_cast<ModelObject>(original)) 
        {
            auto newModel = std::make_shared<ModelObject>(
                resourceName + "_instance",
                model->GetModel()
            );

            newModel->SetPosition(model->GetPosition());
            newModel->SetRotation(model->GetRotation());
            newModel->SetScale(model->GetScale());

            return newModel;
        }
    }
    return nullptr;
}

ResourceManager& ResourceManager::GetInstance() {
    static ResourceManager instance;

    return instance;
}