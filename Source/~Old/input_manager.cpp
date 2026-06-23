#include "input_manager.h"

void InputManager::ProcessInput(GLFWwindow *window)
{
    // Default Stuff
    current_inputs.esc_down = glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS;

    // Spawning
    current_inputs.space_down = glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS;

    // Movement
    current_inputs.w_hold = glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS;
    current_inputs.s_hold = glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS;
    current_inputs.a_hold = glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS;
    current_inputs.d_hold = glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS;
}

InputState InputManager::GetInputs(){
    return current_inputs;
}