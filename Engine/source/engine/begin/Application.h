#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include "../interface/InterfaceEngine.h"
#include "../input/InputHandler.h"
#include "Viewport.h"
#include "Camera.h"
#include <memory>
#include <string>

class Application {
public:

	Application(int width, int height, std::string_view windowName);
	~Application();

    void ProcessCameraInput(Camera& camera);

    Camera& GetCamera() { return m_camera; }
    bool IsViewportHovered() const { return m_uiEngine.IsViewportHovered(); }

    static Application* GetInstancePtr() { return s_instance; }
    static Application& GetInstance() { return *s_instance; }

    int GetDeltaTime() { return deltaTime; }
    GLFWwindow* GetWindow() const { return m_window; }

    InputHandler& GetInputHandler() { return m_inputHandler; }
    const InputHandler& GetInputHandler() const { return m_inputHandler; }

	void Run();

private:
    void Initialize();
    void MainLoop();
    void Shutdown();

private:
    int m_width;
    int m_height;

    float deltaTime = 0.0f;
    float lastFrame = 0.0f;

    std::string m_windowName;
    GLFWwindow* m_window = nullptr;
    
    static Application* s_instance;

    // Classes inc
    InterfaceEngine m_uiEngine;
    InputHandler m_inputHandler;
    Viewport m_viewport;
    Camera m_camera;

};