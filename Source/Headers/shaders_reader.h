#pragma once

#include <glad/glad.h>

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

std::string ReadShaderFile(const char* path);
unsigned int CompileShader(GLenum shaderType, const char* path);
unsigned int CreateShaderProgram(unsigned int vertexShader, unsigned int fragmentShader);