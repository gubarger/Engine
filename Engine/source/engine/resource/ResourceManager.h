#pragma once
#include <map>
#include <vector>
#include <memory>
#include "../object/GameObject.h"

class ResourceManager {
public:
	static ResourceManager& GetInstance();

	void LoadResources(const std::string& path2D, const std::string& path3D);

	// getters 2D and 3D obj
	const std::vector<std::shared_ptr<GameObject>>& Get2DObjects() const { return m_2DObjects; }
	const std::vector<std::shared_ptr<GameObject>>& Get3DObjects() const { return m_3DObjects; }

	std::shared_ptr<GameObject> CreateInstance(const std::string& resourceName);

private:
	ResourceManager() = default;

private:
	std::map<std::string, std::shared_ptr<GameObject>> m_resourceTemplates;

	std::vector<std::shared_ptr<GameObject>> m_2DObjects;
	std::vector<std::shared_ptr<GameObject>> m_3DObjects;
};