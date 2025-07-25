#pragma once
#include <imgui.h>

class InterfaceEngine {
public:
	InterfaceEngine() = default;

	void SetupStyle() const;
	void Render(unsigned int viewportTexture, const ImVec2& viewportSize);
	
	bool NoHandler() { return m_NoHandler; }
	void ToggleUI() { m_visible = !m_visible; }
	bool IsUIVisible() const { return m_visible; }

private:
	void RenderObjectInterface();

private:
	bool m_NoHandler = false;
	bool m_visible = true;

};