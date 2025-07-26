#pragma once

#include "GameObject.h"
#include "Model.h"
#include "../shader/Shader.h"

class ModelObject : public GameObject {
public:
	ModelObject(const std::string& name, std::shared_ptr<Model> model);

	void Render(Shader& shader) const override;
	
	void SetName(const std::string& name) { m_name = name; }

	std::shared_ptr<Model> GetModel() const { return m_model; }

private:
	std::shared_ptr<Model> m_model;

};