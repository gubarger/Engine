#include "InterfaceEngine.h"

void InterfaceEngine::SetupStyle() const {
	ImGuiStyle& style = ImGui::GetStyle();

	// Setting up rounding and indentation
	style.WindowRounding = 5.0f;
	style.FrameRounding = 3.0f;
	style.ScrollbarRounding = 5.0f;
	style.GrabRounding = 2.0f;
	style.PopupRounding = 5.0f;
}

void InterfaceEngine::Render() {
	if (!m_visible) return;

	RenderObjectInterface();
}

void InterfaceEngine::RenderObjectInterface() {
	ImGui::SetNextWindowSize(ImVec2(200, 720), ImGuiCond_FirstUseEver);
	ImGui::SetNextWindowPos(ImVec2(0, 0), ImGuiCond_FirstUseEver);

	ImGui::Begin("Object", nullptr, ImGuiWindowFlags_NoSavedSettings);
	{
		ImGui::Text("TestWindow");
		ImGui::Separator();
		ImGui::Spacing();
	}
	ImGui::End();
}