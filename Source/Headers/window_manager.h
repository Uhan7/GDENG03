#pragma once

#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

GLFWwindow* SetupWindow(int width, int height, const char *title, GLFWmonitor *monitor, GLFWwindow *share);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);