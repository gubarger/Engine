#include "InputHandler.h"
#include <GLFW/glfw3.h>

void InputHandler::HandleKey(int key, int action, int mods) const {
    if (action != GLFW_PRESS) return;

    if (key == GLFW_KEY_F1 && (mods & GLFW_MOD_CONTROL)) 
    {
        // Closing logic in the Application class
    }
    else if (key == GLFW_KEY_TAB && (mods & GLFW_MOD_SHIFT)) 
    {
        m_uiEngine.ToggleUI();
    }
}