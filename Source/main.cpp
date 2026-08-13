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
#include "level_data.h"
#include "window_manager.h"
#include "input_manager.h"
#include "shaders_reader.h"
#include "Camera_Scripts/camera.h"
#include "Camera_Scripts/perspective_camera.h"
#include "Camera_Scripts/orthographic_camera.h"

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

    // Setup the.. level??
    LevelData level;

    // Load up into level
    LevelObject obj;
    obj.type = PrimitiveType::Capsule;
    obj.position = glm::vec3(0.0f, 1.0f, 0.0f);
    obj.scale = glm::vec3(1.0f, 2.0f, 1.0f);
    obj.hasRigidBody = true;
    level.objects.push_back(obj);

    // Setup our shaders
    unsigned int vertexShader = CompileShader(GL_VERTEX_SHADER, "Shaders/default.vert");
    unsigned int fragmentShader = CompileShader(GL_FRAGMENT_SHADER, "Shaders/default.frag");
    unsigned int shaderProgram = CreateShaderProgram(vertexShader, fragmentShader);

    // Setup Mouse
    glm::dvec2 currentMousePosition = {0.0, 0.0};
    glm::vec2 lastMousePosition = {SCR_WIDTH / 2.0f, SCR_HEIGHT / 2.0f};
    float mouseSensitivity = 0.1f;

    // Setup Key Input
    glfwSetKeyCallback(window, key_callback);
    glfwSetMouseButtonCallback(window, mouse_button_callback);

    // Make our epic camera
    PerspectiveCamera camera(glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.0f, -90.0f, 0.0f));
    float cameraNormalSpeed = 0.01f;
    float cameraFastSpeed = 0.03f;
    camera.cameraMoveSpeed = cameraNormalSpeed;
    glEnable(GL_DEPTH_TEST);

    // Make textures if needed
    

    // Make our Objects
    Cube cube = Cube(glm::vec3(0, 0, 0), 1, glm::vec3(0.33f, 0.67f, 1));
    Capsule capsule = Capsule(glm::vec3(2, 2, 0), 1, 3, glm::vec3(0.33f, 0.67f, 1));

    
    // Setup IMGUI
    SetUpImGui(window);
    ImGuiIO& io = ImGui::GetIO();
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

    // UPDATE EVERY FRAME =====================================================
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

        // Hide Mouse
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED); // We hide + lock the mouse

        // if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT)) glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED); // We hide + lock the mouse
        // else glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

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

        camera.RotateByMouse(xOffset, yOffset);

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
        cube.Draw(shaderProgram);
        capsule.Draw(shaderProgram);

        // Setup IMGUI
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        /*
        {
            static int counter = 0;

            ImGui::Begin("Epic Credits");

            ImGui::Text("GDENG03 Engine by Johann Naranjo");
            ImGui::Text("Done on OpenGL on Mac OS");
            ImGui::ColorEdit3("clear color", (float*)&clear_color);

            if (ImGui::Button("Say Wallahi Bro")){
                std::cout << "Wallahi" << std::endl;
                counter++;
            }

            ImGui::SameLine();
            ImGui::Text("counter = %d", counter);

            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
            ImGui::End();
        }
        */

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
