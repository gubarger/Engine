#pragma once

// Supports so far only .png

#include "GameObject.h"
#include "Texture.h"
#include "../shader/Shader.h"

class SpriteObject : public GameObject {
public:
	SpriteObject(const std::string& name, std::shared_ptr<Texture> texture);
    ~SpriteObject();

	void Render(Shader& shader) const override;

    void SetName(const std::string& name) { m_name = name; }

    std::shared_ptr<Texture> GetTexture() const { return m_texture; }

private:
    std::shared_ptr<Texture> m_texture;
    GLuint m_VAO, m_VBO, m_EBO;
    void SetupMesh();

};