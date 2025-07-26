#pragma once

#include <vector>
#include <memory>
#include "../object/GameObject.h"

class Scene {
public:
	void AddObject(std::shared_ptr<GameObject> object);

	void RemoveObject(const std::string& name);

	const std::string& GetName() const { return m_name; }
	void SetName(const std::string& name) { m_name = name; }

	void Clear() {};
	void Render() const {};

	const std::vector<std::shared_ptr<GameObject>>& GetObjects() const { return m_objects; }

	std::shared_ptr<GameObject> GetObjectByName(const std::string& name) const {};
	std::shared_ptr<GameObject> GetSelectedObject() const {};

private:
	std::string m_name;
	std::vector<std::shared_ptr<GameObject>> m_objects;

};