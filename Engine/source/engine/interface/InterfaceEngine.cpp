#include "InterfaceEngine.h"
#include "../resource/ResourceManager.h"
#include "../begin/SceneManager.h"
#include "../begin/SceneSerializer.h"
#include "../begin/Application.h"

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
				/* COMPLETELY OLD IMPLEMENTATION (to be deleted later) */
	// Object Hierarchy panel

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
}

void InterfaceEngine::RenderHierarchyPanel(std::shared_ptr<Scene> scene) {
	if (!scene) return;

	ImGui::Begin("Hierarchy");
	{
		if (ImGui::Button("+ Create")) 
		{
			auto newObj = std::make_shared<GameObject>("Object", ObjectType::OBJECT_3D);
		
			scene->AddObject(newObj);
			
			m_selectedObject = newObj;
		}
		ImGui::Separator();

		for (auto& obj : scene->GetObjects()) 
		{
			bool selected = (obj == m_selectedObject);

			if (ImGui::Selectable(obj->GetName().c_str(), selected)) 
			{
				m_selectedObject = obj;
			}

			if (ImGui::BeginPopupContextItem())
			{
				if (ImGui::MenuItem("Delete")) 
				{
					if (m_selectedObject == obj)
					{
						m_selectedObject = nullptr;
					}
					scene->RemoveObject(obj->GetName());
				}
				ImGui::EndPopup();
			}
		}

		if (ImGui::BeginDragDropTarget()) 
		{
			if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("PROJECT_OBJECT")) 
			{
				IM_ASSERT(payload->DataSize == sizeof(std::string));
				std::string resourceName = *static_cast<std::string*>(payload->Data);

				auto newObj = ResourceManager::GetInstance().CreateInstance(resourceName);
				
				if (newObj) 
				{
					scene->AddObject(newObj);
					m_selectedObject = newObj;
				}
			}
			ImGui::EndDragDropTarget();
		}
	}
	ImGui::End();
}

void InterfaceEngine::RenderProjectPanel() {
	ImGui::Begin("Project");
	{
		// 2D obj
		if (ImGui::TreeNode("2D Objects"))
		{
			auto& objects = ResourceManager::GetInstance().Get2DObjects();

			for (const auto& obj : objects)
			{
				ImGui::Selectable(obj->GetName().c_str());

				// Start of dragging
				if (ImGui::BeginDragDropSource())
				{
					std::string name = obj->GetName();

					ImGui::SetDragDropPayload("PROJECT_OBJECT", &name, sizeof(std::string));
					ImGui::Text("Add %s to scene", name.c_str());
					ImGui::EndDragDropSource();
				}
			}
			ImGui::TreePop();
		}

		// 2D obj
		if (ImGui::TreeNode("3D Objects"))
		{
			auto& objects = ResourceManager::GetInstance().Get3DObjects();

			for (const auto& obj : objects)
			{
				ImGui::Selectable(obj->GetName().c_str());

				// Start of dragging
				if (ImGui::BeginDragDropSource())
				{
					std::string name = obj->GetName();

					ImGui::SetDragDropPayload("PROJECT_OBJECT", &name, sizeof(std::string));
					ImGui::Text("Add %s to scene", name.c_str());
					ImGui::EndDragDropSource();
				}
			}
			ImGui::TreePop();
		}
	}
	ImGui::End();
}

void InterfaceEngine::RenderSceneManagement() {
	ImGui::Begin("Scene Management");
	{
		auto& sceneManager = SceneManager::GetInstance();

		// Create new scene
		static char newSceneName[128] = "NewScene";

		ImGui::InputText("##NewSceneName", newSceneName, sizeof(newSceneName));
		ImGui::SameLine();

		if (ImGui::Button("Create Scene")) {
			auto scene = std::make_shared<Scene>();

			scene->SetName(newSceneName);
			sceneManager.AddScene(scene);
		}
		ImGui::Separator();

		// Managing the active scene
		if (auto activeScene = sceneManager.GetActiveScene()) {
			ImGui::Text("Active Scene: %s", activeScene->GetName().c_str());

			// Save/Load
			static char savePath[256] = "scenes/scene.json";
			ImGui::InputText("##SavePath", savePath, sizeof(savePath));

			if (ImGui::Button("Save Scene"))
			{
				SceneSerializer::Serialize(*activeScene, savePath);
			}

			ImGui::SameLine();

			if (ImGui::Button("Load Scene"))
			{
				if (auto loadedScene = SceneSerializer::Deserialize(savePath))
				{
					sceneManager.AddScene(loadedScene);
					sceneManager.SetActiveScene(loadedScene->GetName());
				}
			}
		}
	}
	ImGui::End();
}

void InterfaceEngine::RenderInspector(const std::shared_ptr<GameObject>& selectedObject) {
	ImGui::Begin("Inspector");
	{
		if (selectedObject)
		{
			glm::vec3 position = selectedObject->GetPosition();
			if (ImGui::DragFloat3("Position", &position.x, 0.1f)) 
			{
				selectedObject->SetPosition(position);
			}

			glm::vec3 rotation = selectedObject->GetRotation();
			if (ImGui::DragFloat3("Rotation", &rotation.x, 1.0f, -180.0f, 180.0f)) 
			{
				selectedObject->SetRotation(rotation);
			}

			glm::vec3 scale = selectedObject->GetScale();
			if (ImGui::DragFloat3("Scale", &scale.x, 0.1f)) 
			{
				selectedObject->SetScale(scale);
			}

			if (ImGui::Button("Object Settings")) 
			{
				ImGui::OpenPopup("ObjectSettingsPopup");
			}

			if (ImGui::BeginPopup("ObjectSettingsPopup"))
			{
				ImGui::Text("Additional settings for: %s", selectedObject->GetName().c_str());
				ImGui::Separator();

				static glm::vec3 color(1.0f);
				
				if (ImGui::ColorEdit3("Color", &color.x))
				{
					// not yet
				}
				ImGui::EndPopup();
			}
		}
		else 
		{
			ImGui::Text("No object selected");
		}
	}
	ImGui::End();
}

void InterfaceEngine::RenderViewport(unsigned int textureID, const ImVec2& textureSize) {
	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
	ImGui::Begin("Viewport", nullptr, ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse);
	{
		m_viewportSize = ImGui::GetContentRegionAvail();
		m_viewportPos = ImGui::GetWindowPos();

		ImGui::Image(
			(ImTextureID)(uintptr_t)textureID,
			m_viewportSize,
			ImVec2(0, 1),
			ImVec2(1, 0)
		);

		m_isViewportHovered = ImGui::IsWindowHovered();

		if (ImGui::BeginDragDropTarget()) 
		{
			if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("PROJECT_OBJECT")) 
			{
				IM_ASSERT(payload->DataSize == sizeof(std::string));
				std::string resourceName = *static_cast<std::string*>(payload->Data);

				ImVec2 mousePos = ImGui::GetMousePos();
				ImVec2 relativePos = ImVec2(
					mousePos.x - m_viewportPos.x,
					mousePos.y - m_viewportPos.y
				);

				float u = relativePos.x / m_viewportSize.x;
				float v = relativePos.y / m_viewportSize.y;

				auto* app = Application::GetInstancePtr();

				if (app) 
				{
					float aspectRatio = m_viewportSize.x / m_viewportSize.y;
					glm::vec3 worldPos = CalculateWorldPosition(u, v, app->GetCamera(), aspectRatio);

					auto newObj = ResourceManager::GetInstance().CreateInstance(resourceName);
					
					if (newObj) 
					{
						newObj->SetPosition(worldPos);
						SceneManager::GetInstance().GetActiveScene()->AddObject(newObj);
						m_selectedObject = newObj;
					}
				}
			}
			ImGui::EndDragDropTarget();
		}

		if (m_isViewportHovered && !ImGui::IsAnyItemActive()) 
		{
			HandleViewportCamera(Application::GetInstance().GetCamera());
		}
	}
	ImGui::End();
	ImGui::PopStyleVar();
}

void InterfaceEngine::HandleViewportCamera(Camera& camera) {
	if (!m_isViewportHovered) return;

	if (ImGui::IsMouseDragging(ImGuiMouseButton_Right)) 
	{
		ImVec2 delta = ImGui::GetMouseDragDelta(ImGuiMouseButton_Right);
		camera.ProcessMouseMovement(delta.x, -delta.y);
		ImGui::ResetMouseDragDelta(ImGuiMouseButton_Right);
	}

	float wheel = ImGui::GetIO().MouseWheel;
	
	if (wheel != 0.0f) 
	{
		camera.ProcessMouseScroll(wheel * 2.0f);
	}

	// WASD move
	float speed = 2.5f * Application::GetInstance().GetDeltaTime();
	
	if (ImGui::IsKeyDown(ImGuiKey_W)) camera.Position += camera.Front * speed;
	if (ImGui::IsKeyDown(ImGuiKey_S)) camera.Position -= camera.Front * speed;
	if (ImGui::IsKeyDown(ImGuiKey_A)) camera.Position -= camera.Right * speed;
	if (ImGui::IsKeyDown(ImGuiKey_D)) camera.Position += camera.Right * speed;
}

glm::vec3 InterfaceEngine::CalculateWorldPosition(float u, float v, Camera& camera, float aspectRatio) {
	float ndcX = u * 2.0f - 1.0f;
	float ndcY = 1.0f - v * 2.0f;

	glm::vec4 rayClip(ndcX, ndcY, -1.0f, 1.0f);
	glm::mat4 projection = camera.GetProjectionMatrix(aspectRatio);
	glm::vec4 rayEye = glm::inverse(projection) * rayClip;
	
	rayEye = glm::vec4(rayEye.x, rayEye.y, -1.0f, 0.0f);

	glm::mat4 view = camera.GetViewMatrix();
	glm::vec3 rayWorld = glm::vec3(glm::inverse(view) * rayEye);

	rayWorld = glm::normalize(rayWorld);

	float t = -camera.Position.y / rayWorld.y;
	
	return camera.Position + rayWorld * t;
}

void InterfaceEngine::RenderObjectInterface() {
					/* COMPLETELY OLD IMPLEMENTATION (to be deleted later) */



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