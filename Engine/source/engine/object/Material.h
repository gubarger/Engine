#pragma once

/**
		--------------------------------------
		@The rudiments of working with materials, 
		code that has not yet been completed,
		and mechanics. It will be updated
		--------------------------------------
*/

#include <glm/glm.hpp>
#include <memory>
#include "Texture.h"

class Material {
public:
	Material() = default;

	void SetDiffuse(std::shared_ptr<Texture> texture) { m_diffuse = texture; }
	void SetSpecular(std::shared_ptr<Texture> texture) { m_specular = texture; }
	void SetShininess(float shininess) { m_shininess = shininess; }

	std::shared_ptr<Texture> GetDiffuse() const { return m_diffuse; }
	std::shared_ptr<Texture> GetSpecular() const { return m_specular; }
	float GetShininess() const { return m_shininess; }

private:
	std::shared_ptr<Texture> m_diffuse;
	std::shared_ptr<Texture> m_specular;
	
	float m_shininess = 32.0f;

};