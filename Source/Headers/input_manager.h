#pragma once

#include "window_manager.h"

struct InputState
{
    bool esc_down;
    bool space_down;
    bool delete_despawn;
    bool w_hold;
    bool s_hold;
    bool a_hold;
    bool d_hold;
};

class InputManager
{
    private:
        InputState current_inputs;

    public:
        void ProcessInput(GLFWwindow *window);
        InputState GetInputs();
};