#include "ModelObject.h"

ModelObject::ModelObject(const std::string& name, std::shared_ptr<Model> model)
    : GameObject(name, ObjectType::OBJECT_3D), m_model(model) {
}

void ModelObject::Render(Shader& shader) const {
    if (m_model)
    {
        m_model->Render(shader);
    }
}