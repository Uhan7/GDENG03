// Normal Includes
#include <iostream>
#include <filesystem>
#include <memory>

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

    // Make our epic shits
    vector<unique_ptr<Quad>> squares;
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

        // Move our shits
        for (unique_ptr<Quad>& square : squares){
            square->transform.MoveWithSpeed();
            if (square->transform.position.x > 0.9f || square->transform.position.x < -0.9f) square->transform.speedX *= -1;
            if (square->transform.position.y > 0.9f || square->transform.position.y < -0.9f) square->transform.speedY *= -1;
        }

        // Render our shits
        for (unique_ptr<Quad>& square : squares) square->Draw(shaderProgram);

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
    vector<unique_ptr<Quad>>* squares = static_cast<vector<unique_ptr<Quad>>*>(glfwGetWindowUserPointer(window));

    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) glfwSetWindowShouldClose(window, GLFW_TRUE);
    if (key == GLFW_KEY_SPACE && action == GLFW_PRESS){
        cout << "Spawned!" << endl;
        unique_ptr<Quad> newSquare = Quad::MakeSquare({0.0f, 0.0f, 0.0f}, 0.2f, {RandomFloat(0.f, 1.f), RandomFloat(0.f, 1.f), RandomFloat(0.f, 1.f)});
        newSquare->transform.speedX = RandomFloat(-0.01f, 0.01f);
        newSquare->transform.speedY = RandomFloat(-0.01f, 0.01f);
        squares->push_back(std::move(newSquare));
    }
    if (key == GLFW_KEY_MINUS && action == GLFW_PRESS){
        cout << "Despawned!" << endl;
        if (squares->size() > 0) squares->pop_back();
    }
    if (key == GLFW_KEY_BACKSPACE && action == GLFW_PRESS){
        cout << "Despawned All!" << endl;
        if (squares->size() > 0) squares->clear();
    }
}