#pragma once

/* @Just the beginning of the class, it will be updated later. */

#include <glm/glm.hpp>
#include "../shader/Shader.h"

struct Light {
    glm::vec3 Position;

    glm::vec3 Ambient = glm::vec3(0.2f);
    glm::vec3 Diffuse = glm::vec3(0.5f);
    glm::vec3 Specular = glm::vec3(1.0f);

    void ConfigureShader(Shader& shader, const std::string& name) const {
        shader.setVec3(name + ".position", Position);
        shader.setVec3(name + ".ambient", Ambient);
        shader.setVec3(name + ".diffuse", Diffuse);
        shader.setVec3(name + ".specular", Specular);
    }
};