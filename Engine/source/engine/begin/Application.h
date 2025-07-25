#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include "../interface/InterfaceEngine.h"
#include "../input/InputHandler.h"
#include "Viewport.h"
#include <memory>
#include <string>

// base initialization in _WIN32

class Application {
public:

	Application(int width, int height, std::string_view windowName);
	~Application();
	
	void Run();

private:
    void Initialize();
    void MainLoop();
    void Shutdown();

private:
    int m_width;
    int m_height;
    std::string m_windowName;
    GLFWwindow* m_window = nullptr;
    
    // Classes inc
    InterfaceEngine m_uiEngine;
    InputHandler m_inputHandler;
    Viewport m_viewport;

};