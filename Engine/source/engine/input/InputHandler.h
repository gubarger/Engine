#pragma once

#include "../interface/InterfaceEngine.h"
#include <GLFW/glfw3.h>

class InputHandler {
public:
	explicit InputHandler(InterfaceEngine& uiEngine) : m_uiEngine(uiEngine) {}

	void HandleKey(int key, int action, int mods) const;
	void HandleMouseButton(GLFWwindow* window, int button, int action, int mods, bool viewportHovered);

	bool IsViewportHovered() const { return m_viewportHovered; }
	void SetViewportHovered(bool hovered) { m_viewportHovered = hovered; }
	bool ShouldCaptureMouse() const { return m_rightMousePressed; }

private:
	InterfaceEngine& m_uiEngine;
	bool m_viewportHovered = false;
	bool m_rightMousePressed = false;

};