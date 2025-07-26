#pragma once

#include <glad/glad.h>
#include <vector>
#include <glm/glm.hpp>
#include <memory>
#include <string>
#include "../shader/Shader.h"



class Model {
public:
	Model(const std::string& filePath);

	void Render(Shader& shader) const;

private:
	struct Mesh {
		GLuint VAO, VBO, EBO;
		unsigned int indexCount;
	};

private:
	std::vector<Mesh> m_meshes;

private:
	void LoadModel(const std::string& path);
	void ProcessMesh(
		const std::vector<glm::vec3>& vertices, 
		const std::vector<unsigned int>& indices
	);
};