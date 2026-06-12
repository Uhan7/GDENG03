#include "shaders_reader.h"

string ReadShaderFile(const char* path)
{
    ifstream file(path);
    if (!file.is_open()) {
        cout << "Error: ReadShaderFile failed at path: " << path << endl;
        return "";
    }

    stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

unsigned int CompileShader(GLenum shaderType, const char* path){
    int success;
    char infoLog[512];

    string shaderCode = ReadShaderFile(path);
    const char* shaderSource = shaderCode.c_str();

    unsigned int shader = glCreateShader(shaderType);

    glShaderSource(shader, 1, &shaderSource, nullptr);
    glCompileShader(shader);

    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(shader, 512, nullptr, infoLog);
        cout << "Error: CompileShader Failed. Logs:\n" << infoLog << endl;
    }

    return shader;
}

unsigned int CreateShaderProgram(unsigned int vertexShader, unsigned int fragmentShader){
    int success;
    char infoLog[512];

    unsigned int shaderProgram = glCreateProgram();

    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, nullptr, infoLog);
        cout << "Error: CreateShaderProgram Failed. Logs:\n" << infoLog << endl;
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return shaderProgram;
}