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

int main()
{
    GLFWwindow* window = SetupWindow(SCR_WIDTH, SCR_HEIGHT, "NARANJO GDENG03", nullptr, nullptr);
    if (window == nullptr) return -1;

    unsigned int vertexShader = CompileShader(GL_VERTEX_SHADER, "Shaders/default.vert");
    unsigned int fragmentShader = CompileShader(GL_FRAGMENT_SHADER, "Shaders/default.frag");
    unsigned int shaderProgram = CreateShaderProgram(vertexShader, fragmentShader);

    Quad quad1(
        {-0.4f,  0.4f, 0.0f},
        { 0.5f,  0.5f, 0.0f},
        {-0.5f, -0.5f, 0.0f},
        { 0.4f, -0.4f, 0.0f},
        { 1.0f,  0.0f, 0.0f}
    );
    Quad quad2(
        {-0.9f,  0.9f, 0.0f},
        {-0.6f,  0.5f, 0.0f},
        {-0.9f, -0.9f, 0.0f},
        {-0.6f, -0.5f, 0.0f},
        { 0.0f,  1.0f, 0.0f}
    );
    Quad quad3(
        {-0.5f, -0.6f, 0.0f},
        { 0.5f, -0.6f, 0.0f},
        {-0.7f, -0.9f, 0.0f},
        { 0.7f, -0.9f, 0.0f},
        { 0.0f,  0.0f, 1.0f}
    );

    // UPDATE EVERY FRAME
    while (!glfwWindowShouldClose(window))
    {
        
        processInput(window);

        glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        quad1.Draw(shaderProgram);
        quad2.Draw(shaderProgram);
        quad3.Draw(shaderProgram);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteProgram(shaderProgram);
    glfwTerminate();
    return 0;
}