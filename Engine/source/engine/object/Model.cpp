#include "Model.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <iostream>

Model::Model(const std::string& filePath) {
	LoadModel(filePath);
}

void Model::Render(Shader& shader) const {
    for (const auto& mesh : m_meshes) 
    {
        glBindVertexArray(mesh.VAO);
        {
            glDrawElements(GL_TRIANGLES, mesh.indexCount, GL_UNSIGNED_INT, 0);
        }
        glBindVertexArray(0);
    }
}

void Model::LoadModel(const std::string& path) {
    Assimp::Importer importer;

    const aiScene* scene = importer.ReadFile(
        path,
        aiProcess_Triangulate |
        aiProcess_GenNormals |
        aiProcess_FlipUVs
    );

    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) 
    {
        std::cerr << "Assimp error: " << importer.GetErrorString() << "\n";
        return;
    }

    if (scene->mNumMeshes > 0) 
    {
        aiMesh* mesh = scene->mMeshes[0];

        std::vector<glm::vec3> vertices;
        std::vector<unsigned int> indices;

        for (unsigned int i = 0; i < mesh->mNumVertices; i++) 
        {
            vertices.push_back ({
                mesh->mVertices[i].x,
                mesh->mVertices[i].y,
                mesh->mVertices[i].z
            });
        }

        for (unsigned int i = 0; i < mesh->mNumFaces; i++) 
        {
            aiFace face = mesh->mFaces[i];
        
            for (unsigned int j = 0; j < face.mNumIndices; j++) 
            {
                indices.push_back(face.mIndices[j]);
            }
        }
        ProcessMesh(vertices, indices);
    }
}

void Model::ProcessMesh(
    const std::vector<glm::vec3>& vertices,
    const std::vector<unsigned int>& indices) {
    
    Mesh mesh;
    mesh.indexCount = indices.size();

    glGenVertexArrays(1, &mesh.VAO);
    glGenBuffers(1, &mesh.VBO);
    glGenBuffers(1, &mesh.EBO);

    glBindVertexArray(mesh.VAO);
    {
        glBindBuffer(GL_ARRAY_BUFFER, mesh.VBO);
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), vertices.data(), GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh.EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void*)0);
        glEnableVertexAttribArray(0);
    }
    glBindVertexArray(0);

    m_meshes.push_back(mesh);
}