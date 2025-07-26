#include "GameObject.h"
#include <glm/gtc/matrix_transform.hpp>

GameObject::GameObject(const std::string& name, ObjectType type)
    : m_name(name), m_type(type) {}

glm::mat4 GameObject::GetModelMatrix() const {
    glm::mat4 model = glm::mat4(1.0f);
    {
        model = glm::translate(model, m_position);
        model = glm::rotate(model, glm::radians(m_rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
        model = glm::rotate(model, glm::radians(m_rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
        model = glm::rotate(model, glm::radians(m_rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
        model = glm::scale(model, m_scale);
    }
    return model;
}