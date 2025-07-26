#include "InputHandler.h"
#include <GLFW/glfw3.h>
#include "../begin/Application.h"

void InputHandler::HandleKey(int key, int action, int mods) const {
    if (action != GLFW_PRESS) return;

    if (!m_uiEngine.NoHandler())
    {
        if (key == GLFW_KEY_F1 && (mods & GLFW_MOD_CONTROL))
        {
            // Closing logic in the Application class
        }
        else if (key == GLFW_KEY_TAB && (mods & GLFW_MOD_SHIFT))
        {
            m_uiEngine.ToggleUI(); // due to the new rendering, it temporarily does not work.
        }
    }
}

void InputHandler::HandleMouseButton(GLFWwindow* window, int button, int action, int mods, bool viewportHovered) {
    if (button == GLFW_MOUSE_BUTTON_RIGHT) 
    {
        if (action == GLFW_PRESS && viewportHovered) 
        {
            m_rightMousePressed = true;
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        }
        else if (action == GLFW_RELEASE) 
        {
            m_rightMousePressed = false;
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        }
    }
}