// Normal Includes
#include <iostream>
#include <filesystem>

// Dependencies
#include <glad/glad.h>
#include <GLFW/glfw3.h>

// Source Files
#include "random.h"
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

// Main Function!
int main()
{
    // Setup a Window
    GLFWwindow* window = SetupWindow(SCR_WIDTH, SCR_HEIGHT, "NARANJO GDENG03", nullptr, nullptr);
    if (window == nullptr) return -1;

    // Setup our shaders
    unsigned int vertexShader = CompileShader(GL_VERTEX_SHADER, "Shaders/default.vert");
    unsigned int fragmentShader = CompileShader(GL_FRAGMENT_SHADER, "Shaders/default.frag");
    unsigned int shaderProgram = CreateShaderProgram(vertexShader, fragmentShader);

    // Setup more variables
    float direction = 0.0f;
    float speed = 0.01f;

    // Make our epic shits
    Quad square = Quad::MakeSquare({0.0f, 0.0f, 0.0f}, 0.25f, {1.0f, 1.0f, 1.0f});

    // UPDATE EVERY FRAME
    while (!glfwWindowShouldClose(window))
    {
        // Check for Inputs
        glfwPollEvents();
        glfwSetKeyCallback(window, key_callback);

        // Setup background
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Render our shits
        square.Draw(shaderProgram);

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
    if (key == GLFW_KEY_DELETE && action == GLFW_PRESS) cout << "Despawned!" << endl;
}