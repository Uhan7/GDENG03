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
#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>

// Source Files
#include "random.h"
#include "config.h"
#include "structs.h"
#include "quad.h"
#include "circle.h"
#include "cube.h"
#include "sphere.h"
#include "cylinder.h"
#include "capsule.h"
#include "mesh.h"
#include "texture.h"
#include "Camera_Scripts/camera.h"
#include "Camera_Scripts/perspective_camera.h"
#include "Camera_Scripts/orthographic_camera.h"
#include "window_manager.h"
#include "input_manager.h"
#include "shaders_reader.h"
#include "level_data.h"
#include "level_bios.h"
#include "level_editor.h"
#include "level_renderer.h"

// Prototypes
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
void SetUpImGui(GLFWwindow *window);

// Main Function!
int main()
{
    // Setup a Window
    GLFWwindow* window = SetupWindow(SCR_WIDTH, SCR_HEIGHT, "NARANJO GDENG03", nullptr, nullptr);
    if (window == nullptr) return -1;

    LevelData level;
    LevelEditorState levelEditorState;
    LoadLevelOrCreateDefault(level, levelEditorState.filePath.data());

    // Setup our shaders
    unsigned int vertexShader = CompileShader(GL_VERTEX_SHADER, "Shaders/default.vert");
    unsigned int fragmentShader = CompileShader(GL_FRAGMENT_SHADER, "Shaders/default.frag");
    unsigned int shaderProgram = CreateShaderProgram(vertexShader, fragmentShader);

    // Setup Mouse
    glm::dvec2 currentMousePosition = {0.0, 0.0};
    glm::vec2 lastMousePosition = {SCR_WIDTH / 2.0f, SCR_HEIGHT / 2.0f};
    float mouseSensitivity = 0.1f;
    bool wasRightMouseHeld = false;

    // Setup Key Input
    glfwSetKeyCallback(window, key_callback);
    glfwSetMouseButtonCallback(window, mouse_button_callback);

    // Make our epic camera
    PerspectiveCamera camera(glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.0f, -90.0f, 0.0f));
    float cameraNormalSpeed = 0.01f;
    float cameraFastSpeed = 0.03f;
    camera.cameraMoveSpeed = cameraNormalSpeed;
    glEnable(GL_DEPTH_TEST);

    // Reusable Base Primitives (for the .level tings)
    Quad plane(glm::vec3(-0.5f, 0.0f, -0.5f), glm::vec3( 0.5f, 0.0f, -0.5f), glm::vec3(-0.5f, 0.0f,  0.5f), glm::vec3( 0.5f, 0.0f,  0.5f), glm::vec3(1.0f, 1.0f, 1.0f));
    Cube cube(glm::vec3(0, 0, 0), 1.0f, glm::vec3(1.0f, 1.0f, 1.0f));
    Sphere sphere(glm::vec3(0, 0, 0), 0.5f, glm::vec3(1.0f, 1.0f, 1.0f));
    Capsule capsule(glm::vec3(0, 0, 0), 0.5f, 2.0f, glm::vec3(1.0f, 1.0f, 1.0f));

    // Setup IMGUI
    SetUpImGui(window);
    ImVec4 clear_color = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);

    // UPDATE EVERY FRAME =====================================================
    while (!glfwWindowShouldClose(window))
    {
        // Check for Mouse
        glfwGetCursorPos(window, &currentMousePosition.x, &currentMousePosition.y);

        float xOffset = (float)currentMousePosition.x - lastMousePosition.x;
        float yOffset = lastMousePosition.y - (float)currentMousePosition.y;

        lastMousePosition.x = (float)currentMousePosition.x;
        lastMousePosition.y = (float)currentMousePosition.y;

        // Check for Key Inputs
        glfwPollEvents();

        bool isRightMouseHeld = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS;

        if (isRightMouseHeld) glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        else glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

        if (!isRightMouseHeld || !wasRightMouseHeld){
            lastMousePosition.x = (float)currentMousePosition.x;
            lastMousePosition.y = (float)currentMousePosition.y;
            xOffset = 0.0f;
            yOffset = 0.0f;
        }
        else{
            xOffset *= mouseSensitivity;
            yOffset *= mouseSensitivity;
        }

        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) camera.MovePosition('F');
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) camera.MovePosition('B');
        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) camera.MovePosition('L');
        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) camera.MovePosition('R');
        if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) camera.MovePosition('U');
        if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) camera.MovePosition('D');

        if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) camera.cameraMoveSpeed = cameraFastSpeed;
        else if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE) camera.cameraMoveSpeed = cameraNormalSpeed;

        if (isRightMouseHeld) camera.RotateByMouse(xOffset, yOffset);
        wasRightMouseHeld = isRightMouseHeld;

        // Setup background
        // glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Method of Rendering
        if (glfwGetKey(window, GLFW_KEY_TAB) == GLFW_PRESS) glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        else if (glfwGetKey(window, GLFW_KEY_TAB) == GLFW_RELEASE) glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

        // Update our Camera
        camera.Update(shaderProgram, SCR_WIDTH, SCR_HEIGHT);

        // Update our shits
        

        // Render our shits
        for (const LevelObject& object : level.objects){
            DrawLevelObject(object, plane, cube, sphere, capsule, shaderProgram);
        }

        // Setup IMGUI
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
        DrawLevelEditor(level, levelEditorState);

        // Render IMGUI Stuff
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        // Show next frame
        glfwSwapBuffers(window);
    }

    // Exit IMGUI
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

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

void SetUpImGui(GLFWwindow *window){
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

    ImGui::StyleColorsDark();
    //ImGui::StyleColorsLight();

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 150");
}
