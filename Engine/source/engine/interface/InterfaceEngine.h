#pragma once
#include <imgui.h>

class InterfaceEngine {
public:
	InterfaceEngine() = default;

	void SetupStyle() const;
	void Render();
	
	void ToggleUI() { m_visible = !m_visible; }
	bool IsUIVisible() const { return m_visible; }

private:
	void RenderObjectInterface();

private:
	bool m_visible = true;

};