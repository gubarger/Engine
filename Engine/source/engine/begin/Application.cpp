#include "Application.h"
#include "../engineErrors/EngineDebug.h"
#include "../resource/ResourceManager.h"
#include "SceneManager.h"
#include "../object/ModelObject.h"
#include "../object/SpriteObject.h"
#include "../shader/Shader.h"
#include "../object/3Dobject/Cube.h"

Application* Application::s_instance = nullptr;

Application::Application(int width, int height, std::string_view windowName)
    : m_width(width), m_height(height), m_windowName(windowName),
    m_uiEngine(), m_inputHandler(m_uiEngine) {
    s_instance = this;
    Initialize();
}

Application::~Application() {
	Shutdown();
}

void Application::Initialize() {
    if (!glfwInit()) 
    {
        throw Debuging::Error("GLFW initialization failed");
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    m_window = glfwCreateWindow(m_width, m_height, m_windowName.data(), nullptr, nullptr);
    if (!m_window) 
    {
        glfwTerminate();
        throw Debuging::Error("Window create failed");
    }

    glfwMakeContextCurrent(m_window);
    glfwSwapInterval(1);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) 
    {
        throw Debuging::Error("GLAD initialization failed");
    }

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    // Style imgui
    m_uiEngine.SetupStyle();

    if (!ImGui_ImplGlfw_InitForOpenGL(m_window, true)) 
    {
        throw Debuging::Error("Failed to initialize ImGui GLFW backend!");
    }

    if (!ImGui_ImplOpenGL3_Init("#version 410"))
    {
        throw Debuging::Error("Failed to initialize ImGui OpenGL backend!");
    }

    
    std::vector<std::string> shaderFiles = {
        "source/engine/shader/shader.vert",
        "source/engine/shader/shader.frag",
        "source/engine/shader/sprite.vert",
        "source/engine/shader/sprite.frag"
    };

    for (const auto& file : shaderFiles)
    {
        std::ifstream test(file);
    
        if (!test.is_open())
        {
            std::cerr << "Error: Shader file not found: " << file << "\n";
            throw Debuging::Error("Shader file not found: " + file);
        }
        test.close();
    }

    // Configuring the Input handler
    glfwSetWindowUserPointer(m_window, this);

    auto keyCallback = [](GLFWwindow* w, int k, int s, int a, int m) {
        auto* app = static_cast<Application*>(glfwGetWindowUserPointer(w));
        app->m_inputHandler.HandleKey(k, a, m);
        };

    auto mouseButtonCallback = [](GLFWwindow* w, int button, int action, int mods) {
        auto* app = static_cast<Application*>(glfwGetWindowUserPointer(w));

        bool viewportHovered = app->IsViewportHovered();
        app->GetInputHandler().HandleMouseButton(w, button, action, mods, viewportHovered);

        ImGui_ImplGlfw_MouseButtonCallback(w, button, action, mods);
        };
    glfwSetMouseButtonCallback(m_window, mouseButtonCallback);
    glfwSetKeyCallback(m_window, keyCallback);

    m_viewport.Initialize(1024, 768);
}

void Application::Run() {
    MainLoop();
}

void Application::MainLoop() {
    auto defaultScene = std::make_shared<Scene>();
    defaultScene->SetName("Default");

    SceneManager::GetInstance().AddScene(defaultScene);
    SceneManager::GetInstance().SetActiveScene("Default");

    Camera camera(glm::vec3(0.0f, 0.0f, 5.0f));

    Shader mainShader("source/engine/shader/shader.vert", "source/engine/shader/shader.frag");
    Shader spriteShader("source/engine/shader/sprite.vert", "source/engine/shader/sprite.frag");

    ResourceManager::GetInstance().LoadResources("source/engine/object/2Dobject", "source/engine/object/3Dobject");

    while (!glfwWindowShouldClose(m_window))
    {
        float currentFrame = glfwGetTime();

        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        ProcessCameraInput(camera);

        glfwPollEvents();

        /*
        @Might come in handy someday
        
        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LESS);
        */

        // Render Viewport scene (3D scene)
        m_viewport.BeginFrame();
        auto activeScene = SceneManager::GetInstance().GetActiveScene();

        if (activeScene) 
        {
            glm::mat4 projection = camera.GetProjectionMatrix(
                static_cast<float>(m_viewport.GetSize().x) /
                static_cast<float>(m_viewport.GetSize().y)
            );

            glm::mat4 view = camera.GetViewMatrix();

            for (auto& obj : activeScene->GetObjects()) 
            {
                if (auto modelObj = std::dynamic_pointer_cast<ModelObject>(obj))
                {
                    mainShader.use();
                    {
                        mainShader.setMat4("projection", projection);
                        mainShader.setMat4("view", view);
                        mainShader.setMat4("model", modelObj->GetModelMatrix());
                        mainShader.setVec3("objectColor", glm::vec3(0.8f, 0.3f, 0.2f));
                        // for light
                        /*mainShader.setVec3("lightPos", glm::vec3(2.0f, 2.0f, 2.0f));
                        mainShader.setVec3("viewPos", camera.Position);*/
                    }
                    modelObj->GetModel()->Render(mainShader);
                }
                else if (auto spriteObj = std::dynamic_pointer_cast<SpriteObject>(obj)) 
                {
                    spriteShader.use();
                    {
                        spriteShader.setMat4("projection", projection);
                        spriteShader.setMat4("view", view);
                        spriteShader.setMat4("model", spriteObj->GetModelMatrix());
                    }
                    spriteObj->Render(spriteShader);
                }
            }
        }
        m_viewport.EndFrame();

                                    /** Outdated implementation */
        //if (activeScene) 
        //{
        //    mainShader.use();

        //    glm::mat4 projection = camera.GetProjectionMatrix(
        //        static_cast<float>(m_viewport.GetSize().x) /
        //        static_cast<float>(m_viewport.GetSize().y)
        //    );

        //    glm::mat4 view = camera.GetViewMatrix();
        //    glm::mat4 model = glm::mat4(1.0f);
        //    model = glm::rotate(model, (float)glfwGetTime(), glm::vec3(0.5f, 1.0f, 0.0f));

        //    // Render all obj
        //    for (auto& obj : activeScene->GetObjects()) 
        //    {
        //        if (auto modelObj = std::dynamic_pointer_cast<ModelObject>(obj))
        //        {
        //            mainShader.use();
        //            {
        //                mainShader.setMat4("projection", projection);
        //                mainShader.setMat4("view", view);
        //                mainShader.setMat4("model", glm::mat4(1.0f));
        //                mainShader.setVec3("objectColor", glm::vec3(0.8f, 0.3f, 0.2f));
        //                /*mainShader.setVec3("lightPos", glm::vec3(2.0f, 2.0f, 2.0f));
        //                mainShader.setVec3("viewPos", camera.Position);*/
        //            }
        //            modelObj->GetModel()->Render(mainShader);
        //        }
        //        else if (auto spriteObj = std::dynamic_pointer_cast<SpriteObject>(obj))
        //        {
        //            spriteShader.use();
        //            {
        //                spriteShader.setMat4("projection", projection);
        //                spriteShader.setMat4("view", view);
        //                spriteShader.setMat4("model", obj->GetModelMatrix());
        //            }
        //            spriteObj->Render(spriteShader);
        //        }
        //    }
        //}
        //m_viewport.EndFrame();

        int width, height;
        glfwGetFramebufferSize(m_window, &width, &height);

        if (width == 0 || height == 0) continue;

        glViewport(0, 0, width, height);
        glClearColor(0.2f, 0.2f, 0.2f, 1.00f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Render UI
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // Render ALL
        m_uiEngine.RenderSceneManagement();
        m_uiEngine.RenderProjectPanel();
        m_uiEngine.RenderHierarchyPanel(SceneManager::GetInstance().GetActiveScene());
        m_uiEngine.RenderInspector(m_uiEngine.GetSelectedObject());
        m_uiEngine.RenderViewport(m_viewport.GetTextureID(), ImVec2(m_viewport.GetWidth(), m_viewport.GetHeight()));

        if (m_uiEngine.IsViewportHovered()) 
        {
            auto& app = Application::GetInstance();
            m_uiEngine.HandleViewportCamera(app.GetCamera());
        }

        static ImVec2 lastSize = { 0, 0 };

        ImVec2 currentSize = ImVec2(width, height);
        if (lastSize.x != currentSize.x || lastSize.y != currentSize.y)
        {
            // Updating window sizes when changing
            lastSize = currentSize;
        }

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        glfwSwapBuffers(m_window);
    }
}

void Application::ProcessCameraInput(Camera& camera) {
    /* Camera movement with the right mouse button held down */
    if (m_inputHandler.ShouldCaptureMouse())
    {
        double xpos, ypos;

        glfwGetCursorPos(m_window, &xpos, &ypos);

        static float lastX = xpos, lastY = ypos;
        float xoffset = xpos - lastX;
        float yoffset = lastY - ypos;

        lastX = xpos;
        lastY = ypos;

        camera.ProcessMouseMovement(xoffset, yoffset);

        // When Misha's right button is pressed on the render window
        if (m_uiEngine.IsViewportHovered()) 
        {
            glm::vec3 direction(0.0f);

            if (glfwGetKey(m_window, GLFW_KEY_W) == GLFW_PRESS)
                direction += camera.Front;
            if (glfwGetKey(m_window, GLFW_KEY_S) == GLFW_PRESS)
                direction -= camera.Front;
            if (glfwGetKey(m_window, GLFW_KEY_A) == GLFW_PRESS)
                direction -= camera.Right;
            if (glfwGetKey(m_window, GLFW_KEY_D) == GLFW_PRESS)
                direction += camera.Right;

            if (glm::length(direction) > 0) 
            {
                camera.ProcessKeyboard(glm::normalize(direction), deltaTime);
            }
        }
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