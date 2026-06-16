// Normal Includes
#include <iostream>
#include <filesystem>

// Dependencies
#include <glad/glad.h>
#include <GLFW/glfw3.h>

// Source Files
#include "config.h"
#include "structs.h"
#include "quad.h"
#include "window_manager.h"
#include "input_manager.h"
#include "shaders_reader.h"

// Namespaces
using namespace std;

// Prototypes
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

int main()
{
    // Setup a Window
    GLFWwindow* window = SetupWindow(SCR_WIDTH, SCR_HEIGHT, "NARANJO GDENG03", nullptr, nullptr);
    if (window == nullptr) return -1;

    // Setup our Input Manager
    InputManager input_manager;

    // Setup our shaders
    unsigned int vertexShader = CompileShader(GL_VERTEX_SHADER, "Shaders/default.vert");
    unsigned int fragmentShader = CompileShader(GL_FRAGMENT_SHADER, "Shaders/default.frag");
    unsigned int shaderProgram = CreateShaderProgram(vertexShader, fragmentShader);

    // Setup more variables
    float direction = 0.0f;
    float speed = 0.01f;

    // Draw our epic shits
    Quad quad(
        {-0.4f,  0.4f, 0.0f},
        { 0.5f,  0.5f, 0.0f},
        {-0.5f, -0.5f, 0.0f},
        { 0.4f, -0.4f, 0.0f},
        { 1.0f,  1.0f, 1.0f});

    // UPDATE EVERY FRAME
    while (!glfwWindowShouldClose(window))
    {
        // Setup for checking inputs every frame
        glfwPollEvents();
        input_manager.ProcessInput(window);
        InputState current_inputs = input_manager.GetInputs(); // Bruh do u even need this..

        // // Actual input stuff
        glfwSetKeyCallback(window, key_callback);

        // if (current_inputs.exit){
        //     cout << "Exiting Application!" << endl;
        //     glfwSetWindowShouldClose(window, GLFW_TRUE);
        // }

        // // Spawning and Deleting
        // if (current_inputs.spawn) cout << "Spawned!" << endl;
        // if (current_inputs.despawn) cout << "Despawned!" << endl;

        // Movement
        // if (current_inputs.move_up) quad.transform.position.y += speed;
        // if (current_inputs.move_down) quad.transform.position.y -= speed;
        // if (current_inputs.move_left) quad.transform.position.x -= speed;
        // if (current_inputs.move_right) quad.transform.position.x += speed;

        // Setup background
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Render our shits
        // quad.Draw(shaderProgram);

        // Show next frame
        glfwSwapBuffers(window);
    }

    // Exit the program
    glDeleteProgram(shaderProgram);
    glfwTerminate();
    return 0;
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) glfwSetWindowShouldClose(window, GLFW_TRUE);
    if (key == GLFW_KEY_SPACE && action == GLFW_PRESS) cout << "Spawned!" << endl;
}