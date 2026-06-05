#include "Dependencies/include/GLFW/glfw3.h"

#define N1 1.20711/2 //0.603555
#define N2 0.5/2
#define C 1-0.603555

int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(800, 800, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        glBegin(GL_POLYGON);
        glVertex2f(N2, N1 + C);
        glVertex2f(N1, N2 + C);
        glVertex2f(N1, -N2 + C);
        // glVertex2f(N2, -N1 + C);
        // glVertex2f(-N2, -N1 + C);
        // glVertex2f(-N1, -N2 + C);
        // glVertex2f(-N1, N2 + C);
        // glVertex2f(-N2, N1 + C);
        glEnd(); 

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}