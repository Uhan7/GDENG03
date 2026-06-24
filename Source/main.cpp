// Normal Includes
#include <iostream>
#include <filesystem>
#include <string>
#include <memory>

// Dependencies
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

// Source Files
#include "random.h"
#include "config.h"
#include "structs.h"
#include "quad.h"
#include "window_manager.h"
#include "input_manager.h"
#include "shaders_reader.h"

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

    // Make our epic shits
    std::vector<std::unique_ptr<Quad>> squares;
    glfwSetWindowUserPointer(window, &squares);
    glfwSetKeyCallback(window, key_callback);

    // UPDATE EVERY FRAME
    while (!glfwWindowShouldClose(window))
    {
        // Check for Inputs
        glfwPollEvents();

        // Setup background
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Update our shits
        // Imaginary code

        // Render our shits
        // Imaginary draw code

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
}