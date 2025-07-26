#pragma once
#include <imgui.h>
#include "../begin/Scene.h"
#include "../begin/Camera.h"

class InterfaceEngine {
public:
	InterfaceEngine() = default;

	void SetupStyle() const;
	void Render(unsigned int viewportTexture, const ImVec2& viewportSize);
	
	void RenderHierarchyPanel(std::shared_ptr<Scene> scene);
	void RenderProjectPanel();
	void RenderInspector(const std::shared_ptr<GameObject>& selectedObject);
	void RenderViewport(unsigned int textureID, const ImVec2& textureSize);

	std::shared_ptr<GameObject> GetSelectedObject() const { return m_selectedObject; }
	void SetSelectedObject(std::shared_ptr<GameObject> obj) { m_selectedObject = obj; }

	void HandleViewportCamera(Camera& camera);
	bool IsViewportHovered() const { return m_isViewportHovered; }

	void RenderSceneManagement();

	bool NoHandler() { return m_NoHandler; }
	void ToggleUI() { m_visible = !m_visible; }
	bool IsUIVisible() const { return m_visible; }

	glm::vec3 CalculateWorldPosition(float u, float v, Camera& camera, float aspectRatio);

private:
	void RenderObjectInterface();

private:
	bool m_NoHandler = false;
	bool m_visible = true;
	ImVec2 m_viewportSize;
	ImVec2 m_viewportPos;
	bool m_isViewportHovered = false;
	std::shared_ptr<GameObject> m_selectedObject = nullptr;

};