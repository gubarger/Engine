#pragma once

#include <string>
#include <glm/glm.hpp>
#include <memory>
#include "Model.h"

// types of objects
enum class ObjectType {
	OBJECT_2D,
	OBJECT_3D
};

class GameObject {
public:
	GameObject(const std::string& name, ObjectType type);
	virtual ~GameObject() = default;

	virtual void Render(Shader& shader) const {}

	const std::string& GetName() const { return m_name; }
	ObjectType GetType() const { return m_type; }

	const glm::vec3& GetPosition() const { return m_position; }
	const glm::vec3& GetRotation() const { return m_rotation; }
	const glm::vec3& GetScale() const { return m_scale; }

	void SetPosition(const glm::vec3& position) { m_position = position; }
	void SetRotation(const glm::vec3& rotation) { m_rotation = rotation; }
	void SetScale(const glm::vec3& scale) { m_scale = scale; }

	bool IsSelected() const { return m_selected; }
	void SetSelected(bool selected) { m_selected = selected; }

	glm::mat4 GetModelMatrix() const;

protected:
	std::string m_name;
	ObjectType m_type;
	
	glm::vec3 m_position = { 0.0f, 0.0f, 0.0f };
	glm::vec3 m_rotation = { 0.0f, 0.0f, 0.0f };
	glm::vec3 m_scale = { 1.0f, 1.0f, 1.0f };

	bool m_selected = false;

};