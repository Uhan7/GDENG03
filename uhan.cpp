#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>

using namespace std;

// headers
GLFWwindow* SetUpWindow(int width, int height, const char *title, GLFWmonitor *monitor, GLFWwindow *share);
void SetUpImGui(GLFWwindow *window);

string readShaderFile(const char* path);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);
void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

// structs
struct Vec2{
    float x;
    float y;
};

struct Vec3{
    float x;
    float y;
    float z;
};

struct colorVertex{
    Vec3 position;
    Vec3 color;
};

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 800;

int main()
{
    // variables
    float speed = 0.01f;
    bool show_demo_window = true;
    bool show_another_window = false;
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

    std::string vertexShaderCode = readShaderFile("Shaders/default.vert");
    std::string fragmentShaderCode = readShaderFile("Shaders/default.frag");

    const char* vertexShaderSource = vertexShaderCode.c_str();
    const char* fragmentShaderSource = fragmentShaderCode.c_str();

    // Set Up Window
    GLFWwindow* window = SetUpWindow(SCR_WIDTH, SCR_HEIGHT, "NARANJO GDENG03", NULL, NULL);
    if (window == nullptr) return -1;

    SetUpImGui(window);
    ImGuiIO& io = ImGui::GetIO();

    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    unsigned int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    Vec3 rect1 = {-0.5f,  0.5f, 0.0f};
    Vec3 rect2 = { 0.5f,  0.5f, 0.0f};
    Vec3 rect3 = {-0.5f, -0.5f, 0.0f};
    Vec3 rect4 = { 0.5f, -0.5f, 0.0f};

    Vec3 rect_color = {1.0f, 1.0f, 1.0f};

    colorVertex vertices[] = {
        {rect1, rect_color},
        {rect2, rect_color},
        {rect3, rect_color},
        {rect4, rect_color}
    };

    unsigned int indices[] = {
        0, 1, 2,
        1, 2, 3
    };

    unsigned int VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(colorVertex), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(colorVertex), (void*)sizeof(Vec3));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0); 

    glBindVertexArray(0); 

    // UPDATE EVERY FRAME
    while (!glfwWindowShouldClose(window))
    {
        processInput(window);

        bool select1 = glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS;
        bool select2 = glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS;
        bool select3 = glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS;
        bool select4 = glfwGetKey(window, GLFW_KEY_4) == GLFW_PRESS;

        bool up_held = glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS;
        bool left_held = glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS;
        bool down_held = glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS;
        bool right_held = glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS;
        bool tab_held = glfwGetKey(window, GLFW_KEY_TAB) == GLFW_PRESS;

        int selectedVertex = -1;

        if (select1) selectedVertex = 0;
        else if (select2) selectedVertex = 1;
        else if (select3) selectedVertex = 2;
        else if (select4) selectedVertex = 3;
        else selectedVertex = -1;

        if (selectedVertex >= 0){
            if (up_held) vertices[selectedVertex].position.y += speed;
            if (left_held) vertices[selectedVertex].position.x -= speed;
            if (down_held) vertices[selectedVertex].position.y -= speed;
            if (right_held) vertices[selectedVertex].position.x += speed;
        }

        vertices[0].color = rect_color;
        vertices[1].color = rect_color;
        vertices[2].color = rect_color;
        vertices[3].color = rect_color;

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
        glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        if (tab_held) glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        else glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

        // Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // 2. Show a simple window that we create ourselves. We use a Begin/End pair to create a named window.
        {
            static float f = 0.0f;
            static int counter = 0;

            ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.

            ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
            ImGui::Checkbox("Demo Window", &show_demo_window);      // Edit bools storing our window open/close state
            ImGui::Checkbox("Another Window", &show_another_window);

            ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
            ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color
            ImGui::ColorEdit3("rect color", (float*)&rect_color); // Edit 3 floats representing a color

            if (ImGui::Button("Say Wallahi Bro")){                       // Buttons return true when clicked (most widgets return true when edited/activated)
                cout << "Wallahi" << endl;
                counter++;
            }
            ImGui::SameLine();
            ImGui::Text("counter = %d", counter);

            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
            ImGui::End();
        }

        // 3. Show another simple window.
        if (show_another_window)
        {
            ImGui::Begin("Another Window", &show_another_window);   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
            ImGui::Text("Hello from another window!");
            if (ImGui::Button("Close Me"))
                show_another_window = false;
            ImGui::End();
        }
        
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glDeleteProgram(shaderProgram);

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwTerminate();
    return 0;
}

// Helper functions
GLFWwindow* SetUpWindow(int width, int height, const char *title, GLFWmonitor *monitor, GLFWwindow *share){
    
    // Load GLFW
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    GLFWwindow* window = glfwCreateWindow(width, height, title, monitor, share);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return nullptr;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // Load GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return nullptr;
    }
    return window;
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

string readShaderFile(const char* path)
{
    ifstream file(path);
    stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_SPACE && action == GLFW_PRESS) {
        std::cout << "Spacebar was clicked once!" << std::endl;
    }
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}
