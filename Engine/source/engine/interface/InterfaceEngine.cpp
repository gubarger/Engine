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

void InterfaceEngine::Render(unsigned int viewportTexture, const ImVec2& viewportSize) {
	if (!m_visible) return;

	// Rendering side panels
	RenderObjectInterface();

								/** @Panels */
	// Object Hierarchy panel
	ImGui::Begin("Hierarchy", nullptr, ImGuiWindowFlags_NoSavedSettings);
	{
		ImGui::SetWindowSize(ImVec2(200, 720), ImGuiCond_FirstUseEver);
		ImGui::SetWindowPos(ImVec2(0, 0), ImGuiCond_FirstUseEver);
	}
	ImGui::End();

	// Properties panel
	ImGui::Begin("Properties", nullptr, ImGuiWindowFlags_NoSavedSettings);
	{
		ImGui::SetWindowSize(ImVec2(1080, 100), ImGuiCond_FirstUseEver);
		ImGui::SetWindowPos(ImVec2(200, 0), ImGuiCond_FirstUseEver);
	}
	ImGui::End();

	// Toolbar panel
	ImGui::Begin("Toolbar", nullptr, ImGuiWindowFlags_NoSavedSettings);
	{
		ImGui::SetWindowSize(ImVec2(220, 628), ImGuiCond_FirstUseEver);
		ImGui::SetWindowPos(ImVec2(1065, 100), ImGuiCond_FirstUseEver);

					/* Do not use keyboard shortcuts */
		ImGui::Checkbox("Do not use keyboard shortcuts", &m_NoHandler);
		ImGui::SameLine();
		ImGui::TextDisabled("?");
		if (ImGui::IsItemHovered())
		{
			ImGui::SetTooltip("This function removes keyboard shortcuts.");
		}
	}
	ImGui::End();

	// Status bar
	ImGui::Begin("Status", nullptr, ImGuiWindowFlags_NoSavedSettings);
	{
		ImGui::SetWindowSize(ImVec2(865, 105), ImGuiCond_FirstUseEver);
		ImGui::SetWindowPos(ImVec2(200, 615), ImGuiCond_FirstUseEver);
	}
	ImGui::End();

	// ImGuiCond_Always

	// Main viewport
	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
	ImGui::Begin("Viewport", nullptr, ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse & ImGuiWindowFlags_NoSavedSettings);
	{
		// size while maintaining proportions
		ImVec2 availSize = ImGui::GetContentRegionAvail();
		ImVec2 newSize = availSize;

		ImGui::SetWindowSize(ImVec2(865, 515), ImGuiCond_FirstUseEver);
		ImGui::SetWindowPos(ImVec2(200, 100), ImGuiCond_FirstUseEver);

		// Keeping the proportions
		if (viewportSize.x > 0 && viewportSize.y > 0)
		{
			float aspect = viewportSize.x / viewportSize.y;

			newSize.y = availSize.y;
			newSize.x = availSize.y * aspect;

			if (newSize.x > availSize.x)
			{
				newSize.x = availSize.x;
				newSize.y = availSize.x / aspect;
			}

			// Centering
			ImVec2 offset = ImVec2(
				(availSize.x - newSize.x) * 0.5f,
				(availSize.y - newSize.y) * 0.5f
			);

			// cursor position, current position + offset
			ImVec2 currentPos = ImGui::GetCursorPos();
			ImGui::SetCursorPos(ImVec2(
				currentPos.x + offset.x,
				currentPos.y + offset.y
			));
		}

		// Displays the rendering texture
		ImGui::Image(
			(ImTextureID)(uintptr_t)viewportTexture,
			newSize,
			ImVec2(0, 1),
			ImVec2(1, 0)
		);

		// future input processing for camera/scene
		if (ImGui::IsWindowHovered()) {}
	}
	ImGui::End();
	ImGui::PopStyleVar();
}

void InterfaceEngine::RenderObjectInterface() {
	//ImGui::SetNextWindowSize(ImVec2(200, 720), ImGuiCond_FirstUseEver);
	////ImGui::SetNextWindowPos(ImVec2(0, 0), ImGuiCond_FirstUseEver);

	//ImGui::Begin("Object", nullptr, ImGuiWindowFlags_NoSavedSettings & ImGuiWindowFlags_NoResize);
	//{
	//	ImGui::Text("TestWindow");
	//	ImGui::Separator();
	//	ImGui::Spacing();
	//}
	//ImGui::End();
}