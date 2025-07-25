#include "Application.h"
#include "../debug/logging.h"

Application::Application(int width, int height, std::string_view windowName)
	: m_width(width), m_height(height), m_windowName(windowName),
	m_uiEngine(), m_inputHandler(m_uiEngine) {
	Initialize();
}

Application::~Application() {
	Shutdown();
}

void Application::Initialize() {
    if (!glfwInit()) 
    {
        throw Logging::Error("GLFW initialization failed");
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    m_window = glfwCreateWindow(m_width, m_height, m_windowName.data(), nullptr, nullptr);
    if (!m_window) 
    {
        glfwTerminate();
        throw Logging::Error("Window create failed");
    }

    glfwMakeContextCurrent(m_window);
    glfwSwapInterval(1);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) 
    {
        throw Logging::Error("GLAD initialization failed");
    }

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    // Style imgui
    m_uiEngine.SetupStyle();

    if (!ImGui_ImplGlfw_InitForOpenGL(m_window, true)) 
    {
        throw Logging::Error("Failed to initialize ImGui GLFW backend!");
    }

    if (!ImGui_ImplOpenGL3_Init("#version 410"))
    {
        throw Logging::Error("Failed to initialize ImGui OpenGL backend!");
    }

    // Configuring the Input handler
    glfwSetWindowUserPointer(m_window, this);

    auto keyCallback = [](GLFWwindow* w, int k, int s, int a, int m) {
        auto* app = static_cast<Application*>(glfwGetWindowUserPointer(w));
        app->m_inputHandler.HandleKey(k, a, m);
        };

    glfwSetKeyCallback(m_window, keyCallback);
}

void Application::Run() {
    MainLoop();
}

void Application::MainLoop() {
    while (!glfwWindowShouldClose(m_window)) 
    {
        glfwPollEvents();

        int width, height;
        glfwGetFramebufferSize(m_window, &width, &height);

        if (width == 0 || height == 0) continue;

        glViewport(0, 0, width, height);
        glClearColor(0.45f, 0.55f, 0.60f, 1.00f);
        glClear(GL_COLOR_BUFFER_BIT);

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        m_uiEngine.Render();

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(m_window);
    }
}

void Application::Shutdown() {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    if (m_window) 
    {
        glfwDestroyWindow(m_window);
    }

    glfwTerminate();
}