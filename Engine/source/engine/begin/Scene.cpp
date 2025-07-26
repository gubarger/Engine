#include "Scene.h"

void Scene::AddObject(std::shared_ptr<GameObject> object) {
	m_objects.push_back(object);
}

void Scene::RemoveObject(const std::string& name) {
	m_objects.erase(std::remove_if(m_objects.begin(), m_objects.end(),
		[&name](const auto& obj) { return obj->GetName() == name; }), m_objects.end());
}