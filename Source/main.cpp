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
#include "circle.h"
#include "cube.h"
#include "sphere.h"
#include "cylinder.h"
#include "window_manager.h"
#include "input_manager.h"
#include "shaders_reader.h"
#include "Camera_Scripts/camera.h"
#include "Camera_Scripts/perspective_camera.h"
#include "Camera_Scripts/orthographic_camera.h"

// Prototypes
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);

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

    // Make our epic camera
    PerspectiveCamera camera(glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.0f, -90.0f, 0.0f));
    float cameraNormalSpeed = 0.01f;
    float cameraFastSpeed = 0.03f;
    camera.cameraMoveSpeed = cameraNormalSpeed;
    glEnable(GL_DEPTH_TEST);

    // Make our epic shits
    std::vector<std::unique_ptr<Cube>> cubes;
    for (int i = 0; i < 50; i++){
        cubes.push_back(std::make_unique<Cube>(RandomVec3(-3.0f, 3.0f), 0.5f, glm::vec3{1.0f, 1.0f, 1.0f}));
        cubes.back()->transform.angularVelocity = RandomVec3(-1.0f, 1.0f);
    }

    // Setup Mouse
    glm::dvec2 currentMousePosition = {0.0, 0.0};
    glm::vec2 lastMousePosition = {SCR_WIDTH / 2.0f, SCR_HEIGHT / 2.0f};
    float mouseSensitivity = 0.1f;

    // Setup Key Input
    glfwSetKeyCallback(window, key_callback);
    glfwSetMouseButtonCallback(window, mouse_button_callback);

    // UPDATE EVERY FRAME
    while (!glfwWindowShouldClose(window))
    {
        // Check for Mouse
        glfwGetCursorPos(window, &currentMousePosition.x, &currentMousePosition.y);

        float xOffset = (float)currentMousePosition.x - lastMousePosition.x;
        float yOffset = lastMousePosition.y - (float)currentMousePosition.y;

        lastMousePosition.x = (float)currentMousePosition.x;
        lastMousePosition.y = (float)currentMousePosition.y;
        xOffset *= mouseSensitivity;
        yOffset *= mouseSensitivity;

        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED); // We hide + lock the mouse

        // Check for Key Inputs
        glfwPollEvents();

        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) camera.MovePosition('F');
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) camera.MovePosition('B');
        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) camera.MovePosition('L');
        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) camera.MovePosition('R');
        if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) camera.MovePosition('U');
        if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) camera.MovePosition('D');

        if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) camera.cameraMoveSpeed = cameraFastSpeed;
        else if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE) camera.cameraMoveSpeed = cameraNormalSpeed;

        // if (glfwGetKey(window, GLFW_KEY_I) == GLFW_PRESS) camera.Rotate('U');
        // if (glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS) camera.Rotate('L');
        // if (glfwGetKey(window, GLFW_KEY_K) == GLFW_PRESS) camera.Rotate('D');
        // if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS) camera.Rotate('R');

        camera.RotateByMouse(xOffset, yOffset);

        // Setup background
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Update our Camera
        camera.Update(shaderProgram, SCR_WIDTH, SCR_HEIGHT);

        // Update our shits
        for (std::unique_ptr<Cube>& cube : cubes) cube->transform.RotateWithAngularVelocity();

        // Render our shits
        for (std::unique_ptr<Cube>& cube : cubes) cube->Draw(shaderProgram);

        // Method of Rendering
        if (glfwGetKey(window, GLFW_KEY_TAB) == GLFW_PRESS) glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        else if (glfwGetKey(window, GLFW_KEY_TAB) == GLFW_RELEASE) glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

        // Show next frame
        glfwSwapBuffers(window);
    }

    // Exit the program
    glDeleteProgram(shaderProgram);
    glfwTerminate();
    return 0;
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods){
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) glfwSetWindowShouldClose(window, GLFW_TRUE);
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods){
    if (button == GLFW_MOUSE_BUTTON_RIGHT){
        if (action == GLFW_PRESS) std::cout << ("RMB Yes") << std::endl;
        else if (action == GLFW_RELEASE) std::cout << ("RMB No") << std::endl;
    }
}